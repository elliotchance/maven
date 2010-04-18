/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_find.h"
#include "compiler_strings.h"
#include "compiler_push.h"
#include "compiler_dissect.h"
#include "compiler_operators.h"
#include "doc.h"

MavenFunction dissectFunction(MavenCompiler* c, string line) {
	MavenFunction f;
	StringList parts = smartTokens(line);
	if(parts.length() < 2)
		return f;
	
	// the keywords must go in this order
	// public/private external static returnType functionName(args) alias system func exports func
	f.atLine = c->lineNumber;
	
	// read keywords in order
	int i = 0;
	if(parts[i] == "external") ++i;
	
	if(parts[i] == "public") {
		f.isPublic = true;
		++i;
	} else if(parts[i] == "private") {
		f.isPublic = false;
		++i;
	}
	
	if(parts[i] == "static") {
		f.isStatic = true;
		++i;
	}
	
	// if the expected return type is the same name as the class this COULD
	// BE a constructor, it could also just be a normal return type
	if(/*parts[i] == c->currentClass &&*/ parts[i + 1][0] == '(') {
		f.returnType = "<constructor>";
		//--i;
	} else {
		f.returnType = findMavenObjectPath(c, parts[i++]);
		if(f.returnType == MAVEN_INVALID) {
			printAllNamespaces(c);
			pushError(c, "Unknown object type %s", parts[i - 1]);
			return f;
		}
	}
	
	// function name
	f.name = parts[i++];
	if(f.name.length() > 8 && f.name.substr(0, 8) == "operator") {
		f.name = translateOperatorFunction(f.name);
		//cout << f.name << " -> " << translateOperatorFunction(f.name) << endl;
	}
	
	// function arguments
	smartAssertMessage(i < parts.length(),
				"i = %d, parts.length() = %d", i, parts.length());
	f.args = dissectArguments(c, parts[i++]);
	
	// if the function is not inside a class it has to be static and public
	if(c->currentClass == MAVEN_BARE_CLASS) {
		f.isStatic = true;
		f.isPublic = true;
	}
	
	// allowed exit point
	if(i == parts.length())
		return f;
	
	// get message identifer
	if(parts[i][0] == '[') {
		f.descArgs = "";
		for(int j = 1; j < parts[i].length(); ++j) {
			if(parts[i][j] == ']')
				break;
			f.descArgs += parts[i][j];
		}
		++i;
	}
	
	// allowed exit point
	if(i == parts.length())
		return f;
	
	// get export
	if(parts[i] == "alias") {
		++i;
		if(parts[i] == "system") {
			f.alias_system = true;
			++i;
		}
		f.alias = parts[i++];
	}
	if(i == parts.length())
		return f;
	
	if(parts[i] == "exports") {
		MavenFunction exports;
		exports.returnType = f.returnType;
		exports.name = parts[i + 1];
		if(!f.isStatic) {
			MavenVariable self;
			self.name = "self";
			self.type = "maven.String";
			exports.args.push(self);
		}
		exports.isStatic = f.isStatic;
		for(int i = 0; i < f.args.length(); ++i)
			exports.args.push(f.args[i]);
		exports.alias_system = f.alias_system;
		if(!exports.alias_system)
			exports.alias = c->currentNamespace + "." + c->currentClass + "." + f.name;
		else exports.alias = f.alias;
		exports.isExported = true;
		pushFunction(c, 0, 0, exports);
	}
	
	return f;
}
