/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "strings.h"
#include "errors.h"
#include "scope.h"
#include "constants.h"
#include "keywords.h"
#include "variables.h"
#include "output.h"
#include "objects.h"
#include "functions.h"
#include "namespaces.h"
#include "compiler.h"

bool compileBlock(MavenCompiler* c, string identifier, string code, int mode) {
	string close = "";
	bool closeClass = false, closeFunction = false, closeSwitch = false, closeWith = false;
	MavenVariable toAssign;
	
	// if this is an enum, we process it somewhere else
	identifier = trim(identifier);
	if(mode == MAVEN_ONLY_MAP && identifier.length() > 3 && identifier.substr(0, 4) == "enum") {
		keywordEnum(c, identifier, code);
		return true;
	}
	
	// create the localScope
	if(mode == MAVEN_ONLY_COMPILE)
		newLocalScope(c);
	
	// dissect the identifier(s), this will write to the file
	dissectIdentifer(c, identifier, mode, closeFunction, closeClass, closeSwitch, closeWith, toAssign, close);
	
	// is isArray comes back as true the block contains array elements to be checked indervidually
	// and initialised into the array
	if(toAssign.name != "") {
		string elementType = stripRawType(toAssign.type);
		StringList elements = splitCommas(code);
		MavenVariable v;
		int namespaceID, objectID;
		bool isLocal;
		string variablePath = resolveVariable(c, toAssign.name, v, namespaceID, objectID, isLocal, false);
		string arrayLine = variablePath + " = new maven::";
		if(!isDataType(elementType))
			arrayLine += "object";
		else arrayLine += elementType;
		writeAutoCPPLine(c, arrayLine + "Array(" + intToString(elements.length()) + ");");
		for(int i = 0; i < elements.length(); ++i) {
			arrayLine = variablePath + "->a[" + intToString(i) + "] = ";
			if(!isDataType(elementType))
				arrayLine += string("(") + findObjectPath(c, elementType, true) + ")";
			StringList types;
			MavenMutability mut;
			string dCode = dissectCode(c, elements[i], types, mut);
			if(isDataType(elementType))
				arrayLine += dCode;
			else arrayLine += "new " + findObjectPath(c, nativeToObject(types.join(",")), false) + "(" + dCode + ")";
			writeAutoCPPLine(c, arrayLine + ";");
		}
		return true;
	}
	
	// this loop works by finding a trigger, such as the start of a comment
	// then running a subloop till the end. Rather than having a master loop
	// that tries to keep track of what's going on.
	// This also makes it easier when dealing with scope as each block {}
	// spawn a subloop
	string sub = "";
	int bracketCount = 0;
	bool inQuote = false;
	for(int cursor = 0; cursor < code.length(); ++cursor) {
		char ch = code[cursor];
		
		// make sure we track the line number
		if(ch == '\n') {
			++c->lineNumber;
			++c->totalLines;
		}
		
		// count brackets and quotes
		if(ch == '"' && code[cursor - 1] != '\\') inQuote = !inQuote;
		else if(ch == '(' && !inQuote) ++bracketCount;
		else if(ch == ')' && !inQuote) --bracketCount;
		
		// could be a single line comment
		if(ch == '/' && code[cursor + 1] == '/') {
			cursor += 2;
			for(; cursor < code.length(); ++cursor) {
				char ch = code[cursor];
				
				// we are looking for a new line
				if(ch == '\n' || ch == '\r') {
					++c->lineNumber;
					++c->totalLines;
					break;
				}
			}
			continue;
		}
		
		// could be a multiline comment
		if(ch == '/' && code[cursor + 1] == '*') {
			cursor += 2;
			for(; cursor < code.length(); ++cursor) {
				char ch = code[cursor];
				if(ch == '\n' || ch == '\r') {
					++c->lineNumber;
					++c->totalLines;
				}
				
				// we are looking for a new line
				if(ch == '*' && code[cursor + 1] == '/') {
					++cursor;
					break;
				}
			}
			continue;
		}
		
		// ticks get translated into System.print();
		if(ch == '`') {
			++cursor;
			string catchtick = "";
			for(; cursor < code.length(); ++cursor) {
				char ch = code[cursor];
				
				// we are looking for a close block bracket
				if(ch == '`') {
					if(mode == MAVEN_ONLY_COMPILE)
						compileLine(c, sub + "System.print(" + catchtick + ")");
					break;
				}
				catchtick += ch;
			}
			continue;
		}
		
		// start of a block
		if(ch == '{') {
			++cursor;
			int bracketCount = 1;
			string subblock = "";
			for(; cursor < code.length(); ++cursor) {
				char ch = code[cursor];
				
				// we are looking for a close block bracket
				if(ch == '{') ++bracketCount;
				else if(ch == '}') {
					--bracketCount;
					if(!bracketCount) {
						++c->currentBlockDepth;
						compileBlock(c, sub, subblock, mode);
						--c->currentBlockDepth;
						sub = "";
						break;
					}
				}
				subblock += ch;
			}
			continue;
		}
		
		// case and default for switch
		if(ch == ':' && mode == MAVEN_ONLY_COMPILE) {
			if(startsWith(trim(sub), "case")) {
				if(c->switchArgument == "") {
					pushError(c, "case outside of switch");
					return MAVEN_INVALID;
				}
				
				sub = trim(sub);
				StringList types;
				MavenMutability mut;
				string caseCode = dissectCode(c, sub.substr(4, sub.length() - 4), types, mut, true);
				writeAutoCPPLine(c, "} else if((" + c->switchArgument + ") == (" + caseCode + ")) {");
				sub = "";
				continue;
			} else if(startsWith(trim(sub), "default")) {
				writeAutoCPPLine(c, "} else {");
				sub = "";
				continue;
			}
		}
		
		// end of statement
		if(ch == ';' && !bracketCount) {
			//cout << "sub = '" << sub << "'" << endl;
			if(mode == MAVEN_ONLY_COMPILE)
				compileLine(c, sub);
			else mapLine(c, sub);
			sub = "";
			continue;
		}
		
		// must be code
		sub += ch;
	}
	
	// close
	if(close != "" && mode == MAVEN_ONLY_COMPILE)
		writeAutoCPPLine(c, close);
	if(closeClass) {
		// Object methods
		if(mode == MAVEN_ONLY_MAP) {
			if(c->currentNamespace != "maven" && c->currentClass != "Object") {
				int nID = findNamespaceID(c, c->currentNamespace);
				int oID = findObjectID(c, nID, c->currentClass);
				MavenFunction f;
				
				// Object.copy()
				if(!c->namespaces->at(nID).objects->at(oID)->isAbstract) {
					f.returnType = c->namespaces->at(nID).name + "." + c->namespaces->at(nID).objects->at(oID)->name;
					f.name = "copy";
					f.isConstant = true;
					f.isOverride = true;
					f.isPublic = true;
					pushFunction(c, nID, oID, f);
					
					// skip some classes
					if(f.returnType != "maven.String" && f.returnType != "maven.System" &&
					   f.returnType != "maven.Selector" && f.returnType != "maven.Array") {
						writeCPPLine(c, "} namespace " + c->currentNamespace + "{");
						writeCPPLine(c, f.getCPPLine(c, c->currentClass) + "{");
						writeCPPLine(c, findObjectPath(c, f.returnType, true) + " r = new " +
									 findObjectPath(c, f.returnType, false) + "();");
						for(int i = 0; i < c->namespaces->at(nID).objects->at(oID)->variables->length(); ++i) {
							// skip retain
							if(c->namespaces->at(nID).objects->at(oID)->variables->at(i).name == "retain")
								continue;
							
							// skip static variables
							if(c->namespaces->at(nID).objects->at(oID)->variables->at(i).isStatic)
								continue;
							
							if(isDataType(c->namespaces->at(nID).objects->at(oID)->variables->at(i).type))
								writeCPPLine(c, "r->" + c->namespaces->at(nID).objects->at(oID)->variables->at(i).name +
											 " = this->" + c->namespaces->at(nID).objects->at(oID)->variables->at(i).name + ";");
						}
						writeCPPLine(c, "return r;");
						writeCPPLine(c, "}");
					}
				}
				
				// Object.getClassVariables()
				f.returnType = "maven.ClassVariable[]";
				f.name = "getClassVariables";
				f.isConstant = true;
				f.isOverride = true;
				f.isPublic = true;
				pushFunction(c, nID, oID, f);
				
				// skip some classes
				if(c->currentNamespace != "global") {
					writeCPPLine(c, "} namespace " + c->currentNamespace + "{");
					writeCPPLine(c, f.getCPPLine(c, c->currentClass, false) + " {");
					
					writeCPPLine(c, string("maven::objectArray* variables = new maven::objectArray(") +
								 intToString(c->namespaces->at(nID).objects->at(oID)->variables->length()) + ");");
					writeCPPLine(c, string("variables->a = (maven::Object**) new maven::ClassVariable[") +
								 intToString(c->namespaces->at(nID).objects->at(oID)->variables->length()) + "];");
					
					for(int i = 0; i < c->namespaces->at(nID).objects->at(oID)->variables->length(); ++i)
						writeCPPLine(c, "variables->a[" + intToString(i) +
									 "] = new maven::ClassVariable(true, new maven::String(\"" +
									 c->namespaces->at(nID).objects->at(oID)->variables->at(i).name +
									 "\"), new maven::String(\"" +
									 c->namespaces->at(nID).objects->at(oID)->variables->at(i).type + "\"));");
					
					writeCPPLine(c, "return variables;");
					writeCPPLine(c, "}");
				}
				
				// skip some classes
				if(c->currentNamespace == "global") {
					writeCPPLine(c, "} namespace " + c->currentNamespace + "{");
					
					// Object.callMethodByName()
					f.returnType = "maven.Object";
					f.name = "callMethodByName";
					f.isConstant = true;
					f.isOverride = true;
					f.isPublic = true;
					f.isStatic = false;
					f.args.push(MavenVariable("method", "maven.String"));
					f.args.push(MavenVariable("varargs", "maven.Object[]"));
					pushFunction(c, nID, oID, f);
					
					writeCPPLine(c, f.getCPPLine(c, c->currentClass, false) + " {");
					for(int i = 0; i < c->namespaces->at(nID).objects->at(oID)->functions->length(); ++i) {
						// skip some methods
						if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).isStatic ||
						   c->namespaces->at(nID).objects->at(oID)->functions->at(i).name == "callMethodByName")
							continue;
						
						// no constructors
						if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType == "<constructor>")
							continue;
						
						StringList callArgs;
						for(int j = 0; j < c->namespaces->at(nID).objects->at(oID)->functions->at(i).args.length(); ++j) {
							string toType = nativeToObject(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type).substr(6);
							string toCast = findObjectPath(c, c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type);
							if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type.find("[]") != string::npos) {
								if(isDataType(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type))
									toCast = "maven::" + c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type + "Array*";
								else toCast = "maven::objectArray*";
							}
							
							if(toType != "Object")
								callArgs.push(string("(") + toCast + ") varargs->a[" + intToString(j) + "]->to" + toType + "()");
							else callArgs.push(string("(") + toCast + ") varargs->a[" + intToString(j) + "]");
						}
						
						writeCPPLine(c, string("if(method->operator_3D3D(new maven::String(\"") +
									 c->namespaces->at(nID).objects->at(oID)->functions->at(i).name + "\")) && varargs->length == " +
									 intToString(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args.length()) + ")");
						
						if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType == "void")
							writeCPPLine(c, string("{ ") + c->namespaces->at(nID).objects->at(oID)->functions->at(i).name +
										 "(" + callArgs.join(",") + "); return new maven::Object(); }");
						else {
							string returnType = findObjectPath(c, nativeToObject(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType), false);
							string realFunctionName = c->namespaces->at(nID).objects->at(oID)->functions->at(i).name;
							if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).alias != "")
								realFunctionName = c->namespaces->at(nID).objects->at(oID)->functions->at(i).alias;
							if(returnType != "maven::Object")
								writeCPPLine(c, string("return (maven::Object*) new ") + returnType +
											 "(" + realFunctionName + "(" + callArgs.join(",") + "));");
							else writeCPPLine(c, string("return (maven::Object*) ") +
											  realFunctionName + "(" + callArgs.join(",") + ");");
						}
					}
					
					writeCPPLine(c, "return new maven::Object();");
					writeCPPLine(c, "}");
					
					// Object.callStaticMethodByName()
					f.returnType = "maven.Object";
					f.name = "callStaticMethodByName";
					f.isConstant = true;
					f.isOverride = true;
					f.isPublic = true;
					f.isStatic = true;
					pushFunction(c, nID, oID, f);
					
					writeCPPLine(c, f.getCPPLine(c, c->currentClass, false) + " {");
					for(int i = 0; i < c->namespaces->at(nID).objects->at(oID)->functions->length(); ++i) {
						// skip some methods
						if(!c->namespaces->at(nID).objects->at(oID)->functions->at(i).isStatic ||
						   c->namespaces->at(nID).objects->at(oID)->functions->at(i).name == "callStaticMethodByName")
							continue;
						
						// no constructors
						if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType == "<constructor>")
							continue;
						
						StringList callArgs;
						for(int j = 0; j < c->namespaces->at(nID).objects->at(oID)->functions->at(i).args.length(); ++j) {
							string toType = nativeToObject(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type).substr(6);
							string toCast = findObjectPath(c, c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type);
							if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type.find("[]") != string::npos) {
								if(isDataType(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type))
									toCast = "maven::" + c->namespaces->at(nID).objects->at(oID)->functions->at(i).args[j].type + "Array*";
								else toCast = "maven::objectArray*";
							}
							
							if(toType != "Object")
								callArgs.push(string("(") + toCast + ") varargs->a[" + intToString(j) + "]->to" + toType + "()");
							else callArgs.push(string("(") + toCast + ") varargs->a[" + intToString(j) + "]");
						}
						
						writeCPPLine(c, string("if(method->operator_3D3D(new maven::String(\"") +
									 c->namespaces->at(nID).objects->at(oID)->functions->at(i).name + "\")) && varargs->length == " +
									 intToString(c->namespaces->at(nID).objects->at(oID)->functions->at(i).args.length()) + ")");
						
						if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType == "void")
							writeCPPLine(c, string("{ ") + c->namespaces->at(nID).objects->at(oID)->functions->at(i).name +
										 "(" + callArgs.join(",") + "); return new maven::Object(); }");
						else {
							string returnType = findObjectPath(c, nativeToObject(c->namespaces->at(nID).objects->at(oID)->functions->at(i).returnType), false);
							string realFunctionName = c->namespaces->at(nID).objects->at(oID)->functions->at(i).name;
							if(c->namespaces->at(nID).objects->at(oID)->functions->at(i).alias != "")
								realFunctionName = c->namespaces->at(nID).objects->at(oID)->functions->at(i).alias;
							if(returnType != "maven::Object")
								writeCPPLine(c, string("return (maven::Object*) new ") + returnType +
											 "(" + realFunctionName + "(" + callArgs.join(",") + "));");
							else writeCPPLine(c, string("return (maven::Object*) ") +
											  realFunctionName + "(" + callArgs.join(",") + ");");
						}
					}
					
					writeCPPLine(c, "return new maven::Object();");
					writeCPPLine(c, "}");
				}
			}
		}
		
		// finished with the class
		c->currentClass = MAVEN_BARE_CLASS;
	}
	if(closeFunction)
		c->currentFunction = "";
	if(closeSwitch)
		c->switchArgument = "";
	if(closeWith)
		c->withObject.reset();
	
	// delete the localScope
	if(mode == MAVEN_ONLY_COMPILE)
		deleteLocalScope(c);
	return true;
}
