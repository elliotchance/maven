/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "struct_MavenObject.h"
#include "variables.h"

string compilerFunctionSelector(MavenCompiler* c, string signature, string args, string& type) {
	// find the function we are trying to select
	if(signature.substr(0, 10) != "<Function:") {
		pushError(c, "@selector is not a function");
		return MAVEN_INVALID;
	}
	
	StringList parts = split(',', signature.substr(10, signature.length() - 11));
	int fnID = atoi(parts[0].c_str());
	int foID = atoi(parts[1].c_str());
	int fID = atoi(parts[2].c_str());
	string ptrType = c->namespaces->at(fnID).objects->at(foID)->functions->at(fID).returnType;
	
	// build the selector function
	args = trim(args);
	if(pushSelector(c, args)) {
#if MAVEN_OS == 1
		c->postLines.push_back("void* " + args + "$selector(void* v) {");
#elif MAVEN_OS == 2
		c->postLines.push_back("int " + args + "$selector(void* v) {");
#endif
		c->postLines.push_back("maven::objectArray* argv = (maven::objectArray*) v;");
		if(ptrType != "void")
			c->postLines.push_back(ptrType + " *r = new " + ptrType + "[1];");
		c->postLines.push_back("try {");
		c->postLines.push_back("if(argv->length != " +
							   intToString(c->namespaces->at(fnID).objects->at(foID)->functions->at(fID).args.length()) +
							   ") throw new maven::SelectorException();");
		string caller = "";
		for(int i = 0; i < c->namespaces->at(fnID).objects->at(foID)->functions->at(fID).args.length(); ++i) {
			if(caller != "")
				caller += ",";
			caller += "argv->a[" + intToString(i) + "]->toFloat()";
		}
		c->postLines.push_back(string(c->namespaces->at(fnID).name + "::" +
									  c->namespaces->at(fnID).objects->at(foID)->name + "::" + args + "(") +
							   caller + ");");
		c->postLines.push_back("} catch(maven::Exception* caughtGlobalException) {");
		c->postLines.push_back("  std::cout << caughtGlobalException->description()->s << std::endl;");
		c->postLines.push_back("}");
		if(ptrType != "void") {
#if MAVEN_OS == 1
			c->postLines.push_back("return (void*) r;");
#elif MAVEN_OS == 2
			c->postLines.push_back("return 0;");
#endif
		}
		c->postLines.push_back("}");
	}
	
	// all done
	type = "maven.Selector";
	return "new maven::Selector(" + args + "$selector)";
}
