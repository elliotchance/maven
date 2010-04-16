/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_push.h"
#include "compiler_dissect.h"
#include "keywords.h"
#include "compiler_resolve.h"
#include "compiler_variables.h"
#include "compiler_operators.h"

string dissectSubparseSingle(MavenCompiler* c, string code, string& r, StringList& types, MavenMutability& mut, MavenVariable& prev, bool lastSubparse, string nextOp, StringList argumentTypes, bool warn) {
	code = trim(code);
	
	// a maven.String
	if(isString(code)) {
		types.setTypes("maven.String");
		r = "(new maven::String(" + code + "))";
		return r;
	}
	
	// just grouping brackets
	if(code[0] == '(') {
		r = "(" + dissectCode(c, code.substr(1, code.length() - 2), types, mut) + ")";
		return r;
	}
	
	// chop up
	int findArguments = code.find('('), findElement = code.find('[');
	string newObject = "";
	string newArguments = "";
	
	if(findArguments != string::npos) {
		// bug #60: find_last_of is not appropraite for separating dots
		newArguments = trim(code.substr(findArguments + 1, code.find_last_of(')') - findArguments - 1));
		MavenMutability argumentsMut;
		newArguments = dissectCode(c, newArguments, argumentTypes, argumentsMut);
		newObject = trim(code.substr(0, findArguments));
	}
	
	string newElement = "";
	if(findElement != string::npos)
		// bug #60: find_last_of is not appropraite for separating dots
		newElement = trim(code.substr(findElement + 1, code.find_last_of(']') - findElement - 1));
	
	if(findArguments == string::npos && findElement == string::npos)
		newObject = trim(code);
	else if(findArguments == string::npos && findElement != string::npos)
		newObject = trim(code.substr(0, findElement));
	else if(findArguments != string::npos && findElement != string::npos)
		newObject = trim(code.substr(0, min(findElement, findArguments)));
	
	// a single byte or multibyte characters is converted into its raw int form
	if(code[0] == '\'') {
		if(code.length() <= 4) {
			// if the char constant is upto 2 bytes it's considered a normal char
			types.setTypes("char");
			r = "(char)" + intToString(charToInt(code.substr(1, code.length() - 2)));
			return r;
		} else if(code.length() <= 6) {
			// if the char constant is upto 4 bytes it's considered an integer
			types.setTypes("int");
			r = "(int)" + intToString(charToInt(code.substr(1, code.length() - 2)));
			return r;
		} else {
			// any bigger becomes a problem, tell the user we are only going to be
			// using the first 4 chars
			types.setTypes("int");
			if(warn)
				pushWarning(c, "Only using first 4 bytes of character constant");
			r = "(int)" + intToString(charToInt(code.substr(1, 4)));
			return r;
		}
	}
	
	// setup firstWord variable
	string firstWord = "";
	for(int i = 0; i < code.length(); ++i) {
		// bug #57: make a isWhitespace() function?
		if(code[i] == ' ' || code[i] == '\t' || code[i] == '\n')
			break;
		else firstWord += code[i];
	}
	
	// create an object
	if(firstWord == "new") {
		mut = MU_OK;
		r = "0";
		string newType = "";
		r = keywordNew(c, trim(newObject.substr(3)), newElement, newArguments, newType);
		types.setTypes(newType);
		return r;
	}
	
	MavenVariable resolve;
	bool isLocal;
	int namespaceID, objectID;
	if(prev.type == "") {
		if(findArguments == string::npos) {
			r += resolveVariable(c, newObject, resolve, namespaceID, objectID, isLocal, false);
			prev = resolve;
			string objectPath = findObjectPath(c, stripRawType(prev.type), true);
			if(!isDataType(objectPath) && resolve.type.length() > 0 && resolve.type[0] != '<' &&
			   nextOp != "=")
				r = "(" + objectPath + ")" + r;
			if(newElement != "")
				r += "->a[" + newElement + "]";
			if(resolve.type.length() > 0 && resolve.type[0] != '<')
				r = "(" + r + ")";
		} else {
			int nID = findNamespaceID(c, c->currentNamespace);
			int oID = findObjectID(c, nID, "nil");
			bool found = false;
			for(int i = 0; i < c->namespaces[nID].objects[oID].functions.length(); ++i) {
				// bug #61: check signature (pending)
				if(c->namespaces[nID].objects[oID].functions[i].name == newObject &&
				   canCastBetween(c, argumentTypes.join(","),
								  c->namespaces[nID].objects[oID].functions[i].getSignature(), false, true)) {
					r += "(" + c->currentNamespace + "::nil::" + newObject + "(" + newArguments + "))";
					prev.type = c->namespaces[nID].objects[oID].functions[i].returnType;
					prev.name = "<RETURNED>";
					resolve = prev;
					found = true;
					break;
				}
			}
			
			if(!found) {
				r = MAVEN_INVALID;
				pushError(c, "Can not find function %s(%s)", newObject, argumentTypes.join(","));
				return r;
			}
		}
	} else {
		if(findArguments == string::npos) {
			
			if(prev.type.substr(0, 7) == "<Class:")
				prev.type = prev.type.substr(8, prev.type.length() - 9);
			
			findClass(c, prev.type, namespaceID, objectID);
			bool found = false;
			for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].variables.length(); ++i) {
				if(c->namespaces[namespaceID].objects[objectID].variables[i].name == newObject) {
					resolve = prev = c->namespaces[namespaceID].objects[objectID].variables[i];
					found = true;
					
					string joiner = "->";
					if(c->namespaces[namespaceID].objects[objectID].variables[i].isStatic)
						joiner = "$static::";
					if(!isDataType(c->namespaces[namespaceID].objects[objectID].variables[i].type) &&
					   !lastSubparse)
						pushObjectSafety(c, r + joiner + prev.name);
					if(newElement != "")
						pushArraySafety(c, r + joiner + prev.name, newElement);
					//r = "(" + findObjectPath(c, stripRawType(prev.type), true) + ")";
					r += joiner + prev.name;
					if(newElement != "")
						r += "->a[" + newElement + "]";
					r = "(" + r + ")";
					break;
				}
			}
			
			// bug #58: need to show candidates, see below
			if(!found) {
				r = MAVEN_INVALID;
				pushError(c, "%s does not have the member variable %s", prev.name, newObject);
				return r;
			}
			
		} else {
			
			// perhaps a compiler function
			// bug #59: Incomplete, this code needs to be enabled again.
			if(newObject[0] == '@') {
				/*if(newObject == "@cast")
					return compilerFunctionCast(c, signature, args, type);
				else if(newObject == "@library") {
					// bug #62: this needs to be smarter
					args = trim(args);
					c->extraLibraries.push(combinePaths(c->binDirectory, c->iniFile.getKey("directories.lib")) +
				 args.substr(19, args.length() - 21));
					return "";
				} else if(entity == "@selector")
					return compilerFunctionSelector(c, signature, args, type);
				else if(newObject == "@type")
					//return compilerFunctionType(c, signature, args, type);
				else {
					pushError(c, "Unknown compiler function %s", entity);
					return MAVEN_INVALID;
				}*/
			}
			
			if(prev.type.substr(0, 7) == "<Class:")
				prev.type = prev.type.substr(8, prev.type.length() - 9);
			
			findClass(c, prev.type, namespaceID, objectID);
			int found = 0;
			for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].functions.length(); ++i) {
				// bug #61: check signature (pending)
				if(c->namespaces[namespaceID].objects[objectID].functions[i].name == newObject) {
					found = 1;
					if(canCastBetween(c, argumentTypes.join(","), c->namespaces[namespaceID].objects[objectID].functions[i].getSignature(), false, true)) {
						prev.name = "<RETURNED>";
						prev.type = c->namespaces[namespaceID].objects[objectID].functions[i].returnType;
						resolve = prev;
						found = 2;
						
						string joiner = "->";
						if(c->namespaces[namespaceID].objects[objectID].functions[i].isStatic)
							joiner = "::";
						string objectPath = findObjectPath(c, stripRawType(prev.type), true);
						if(isDataType(objectPath))
							r += joiner;
						else r = "(" + objectPath + ")" + r + joiner;
						
						// deal with an alias
						if(c->namespaces[namespaceID].objects[objectID].functions[i].alias != "")
							r = c->namespaces[namespaceID].objects[objectID].functions[i].alias;
						else r += c->namespaces[namespaceID].objects[objectID].functions[i].name;
						r += "(" + newArguments + ")";
						break;
					}
				}
			}
			if(found == 0) {
				r = MAVEN_INVALID;
				pushError(c, "%s does not have the member method %s", prev.name, newObject + "(" + argumentTypes.join(",") + ")");
				return r;
			} else if(found == 1) {
				r = MAVEN_INVALID;
				// bug #58: need to show candidates
				//if(prev.name[0] == '<')
				pushError(c, "%s does not have the member method to match %s", prev.name, newObject + "(" + argumentTypes.join(",") + ")");
				return r;
			}
		}
	}
	
	// make sure it was resolved
	if(r == MAVEN_INVALID) {
		types.setTypes(MAVEN_INVALID);
		mut = MU_IMPOSSIBLE;
		return r;
	}
	
	if(newElement != "")
		types.setTypes(stripRawType(resolve.type));
	else types.setTypes(resolve.type);
	mut = resolve.mutability;
	if(!isAssignOperator(nextOp))
		r = "((" + findObjectPath(c, types[0], true) + ")" + r + ")";
	return r;
}
