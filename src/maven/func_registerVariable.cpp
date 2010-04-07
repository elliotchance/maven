/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_compilefile.h"
#include "compiler_push.h"
#include "compiler_dissect.h"
#include "compiler_variables.h"
#include "compiler_operators.h"
#include "doc.h"

bool registerVariable(MavenCompiler* c, StringList tokens, bool compiling, MavenVariable& v) {
	// if we are mapping and in the localScope, let the compiler deal with this
	if(!compiling && c->currentFunction != "")
		return true;
	
	// the easiest and safest way to handle this, is to run this function
	// a few times:
	// int a = 1, b = 2;
	int reserved = 0;
	for(; reserved < tokens.length(); ++reserved) {
		if(!isKeyword(c, tokens[reserved]) && !objectExists(c, tokens[reserved]) &&
		   !enumExists(c, tokens[reserved])) break;
	}
	
	// count how many variables we are actually registering?
	StringList separate = splitCommas(tokens.join(" ", reserved, tokens.length() - 1));
	MavenVariable var;
	if(separate.length() > 1) {
		for(int i = 0; i < separate.length(); ++i) {
			var.reset();
			if(!registerVariable(c, smartTokens(tokens.join(" ", 0, reserved - 1) + " " + separate[i]), compiling, var))
				return false;
		}
		return true;
	}
	
	// proceed with single registration
	if(tokens.length() == 1) {
		pushError(c, "Incomplete type, expected variable name");
		return false;
	}
	
	// process tokens
	bool setDefault = true;
	bool isEnum = false;
	for(int i = 0; i < tokens.length() - 1; ++i) {
		if(tokens[i] == "external") v.isExternal = true;
		else if(tokens[i] == "public") v.isPublic = true;
		else if(tokens[i] == "private") v.isPublic = false;
		else if(tokens[i] == "static") v.isStatic = true;
		else if(tokens[i] == "constant") v.mutability = MU_CONSTANT;
		else if(isDataType(stripRawType(tokens[i])) || objectExists(c, stripRawType(tokens[i])))
			v.type = findMavenObjectPath(c, tokens[i]);
		else if(enumExists(c, stripRawType(tokens[i]))) {
			v.type = findMavenEnumPath(c, tokens[i]);
			isEnum = true;
		} else {
			if(tokens[i + 1] == "=") {
				setDefault = false;
				v.name = tokens[i];
				
				// move the array depth from the variable name to the type
				int depth = getArrayDepth(v.name);
				v.name = stripRawType(v.name);
				for(int j = 0; j < depth; ++j)
					v.type += "[]";
				
				StringList vtype;
				MavenMutability m;
				v.defaultValue = dissectCode(c, tokens.join(" ", i + 2, tokens.length() - 1), vtype, m, false);
				if(!canCastBetween(c, vtype.join(","), v.type, false, compiling))
					pushError(c, "Can't cast %s to %s", vtype.join(","), v.type);
				
				if(compiling && c->beforeLine != "")
					writeAutoCPPLine(c, c->beforeLine);
				c->beforeLine = "";
				
				// move default value to main()
				if(c->currentFunction == "") {
					if(compiling) {
						
						// post check for all the objects
						if(c->objectCheck.size() > 0) {
							for(int i = 0; i < c->objectCheck.size(); ++i)
								pushEntryLine(c, "if(" + c->objectCheck[i].key + ") { " + c->objectCheck[i].value + " }");
							c->objectCheck.clear();
						}
						
						pushEntryLine(c, c->currentNamespace + "::" + c->currentClass + "$static::" + v.name + " = " + v.defaultValue + ";");
					}
					v.defaultValue = "";
				}
				
				break;
			} else pushError(c, "Unexpected token '%s'", tokens[i]);
		}
	}
	if(v.name == "")
		v.name = tokens[tokens.length() - 1];
	v.atLine = c->lineNumber;
	v.doc = filterDoc(c, c->doc);
	c->doc = "";
	
	// if the variable name contains '[]' set it as an array
	if(v.name.find("[]") != string::npos) {
		v.name = v.name.substr(0, v.name.find("[]"));
		v.type += "[]";
	}
	
	// set the default value
	if(c->currentFunction == "" && c->currentClass == MAVEN_BARE_CLASS && compiling && setDefault) {
		string defval = "0";
		if(isEnum) {
			int nid = findNamespaceID(c, c->currentNamespace);
			int enumid = findEnumID(c, nid, v.type);
			for(int i = 0; i < c->namespaces[nid].enums[enumid].items.size(); ++i) {
				if(c->namespaces[nid].enums[enumid].items[i].isDefault) {
					defval = intToString(c->namespaces[nid].enums[enumid].items[i].value);
					break;
				}
			}
		}
		pushEntryLine(c, c->currentNamespace + "::" + c->currentClass + "$static::" + v.name + " = " + defval + ";");
	}
	
	// move the array depth from the variable name to the type
	int depth = getArrayDepth(v.name);
	v.name = stripRawType(v.name);
	for(int i = 0; i < depth; ++i)
		v.type += "[]";
	
	// validate name
	if(!validEntityName(v.name))
		pushError(c, "Invalid entity name '%s'", v.name);
	
	int namespaceID = findNamespaceID(c, c->currentNamespace);
	int objectID = findObjectID(c, namespaceID, c->currentClass);
	
	if(compiling && c->currentFunction != "") {
		// FIXME: make sure this is the first time it's being registered
		pushLocalScope(c, v);
		
		if(depth == 0) {
			// FIXME: defval needs to match type
			if(trim(v.defaultValue) == "")
				v.defaultValue = "0";
			writeAutoCPPLine(c, v.getCPP(c) + " = " + v.defaultValue + ";");
		} else writeAutoCPPLine(c, "maven::objectArray* " + v.name + ";");
	} else if(!compiling && c->currentFunction == "") {
		// if the variable is truly bare, it's static
		if(c->currentClass == MAVEN_BARE_CLASS)
			v.isStatic = true;
		
		// make sure this is the first time it's being registered
		
		for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].variables.length(); ++i) {
			if(c->namespaces[namespaceID].objects[objectID].variables[i].name == v.name) {
				cout << "Registering '" << c->namespaces[namespaceID].objects[objectID].variables[i].name
					 << "' Looking in '" << c->namespaces[namespaceID].objects[objectID].name << "'\n";
				/*if(c->namespaces[namespaceID].objects[objectID].variables[i].isInherited)
					pushError(c, "You can not override inherited variable %s", v.name);
				else pushError(c, "Duplicate variable '%s', previously defined at line %s", v.name, intToString(c->namespaces[namespaceID].objects[objectID].variables[i].atLine));
				return false;*/
			}
		}
		
		pushVariable(c, namespaceID, objectID, v);
		if(c->currentClass == MAVEN_BARE_CLASS && tokens.length() > 2) {
			string newline = "";
			for(int i = 1; i < tokens.length(); ++i)
				newline += tokens[i] + " ";
		}
	}
	
	return true;
}
