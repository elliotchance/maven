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
#include "objects.h"
#include "namespaces.h"
#include "variables.h"
#include "doc.h"
#include "keywords.h"
#include "functions.h"
#include "output.h"
#include "scope.h"

/**
 * @brief This function takes a block identifier(s) and returns the c++ processed equivilent.
 */
void dissectIdentifer(MavenCompiler* c, string identifier, int mode, bool& closeFunction, bool& closeClass,
					  bool& closeSwitch, bool& closeWith, MavenVariable& var, string& close) {
	// bug #15: multiple identifiers in one like:
	// its easier to say that a localScope is defined by curly brackets, hence
	// in the case of:
	// for() if() { }
	// is still only a single localScope
	
	// bug #16: Seperately need to test for bracketless nested statements
	// if() if() a;
	identifier = trim(identifier);
	StringList p = splitNested(identifier);
	//if(p.length() == 0) return;
	if(p.length() > 1) {
		// bug #16: which direction should this go?
		for(int i = 0; i < p.length(); ++i)
			dissectIdentifer(c, p[i], mode, closeFunction, closeClass, closeSwitch, closeWith, var, close);
		return;
	}
	
	if(identifier != "") {
		// get the preliminary keyword to see if we can quickly deal with it
		string prelim = "";
		for(int i = 0; i < identifier.length(); ++i) {
			if(!isalnum(identifier[i])) break;
			else prelim += identifier[i];
		}
		c->lastStatament = prelim;
		
		if(prelim == "abstract") {
			StringList words = split(' ', identifier);
			if(words[1] != "class") {
				pushError(c, "Keyword 'class' must follow 'abstract'");
				return;
			} else {
				MavenObject* o = dissectObject(c, identifier);
				c->currentClass = o->name;
				o->isAbstract = true;
				o->doc = filterDoc(c, c->doc);
				c->doc = "";
				if(mode == MAVEN_ONLY_MAP)
					pushObject(c, findNamespaceID(c, c->currentNamespace), o);
				closeClass = true;
			}
		} else if(prelim == "class") {
			MavenObject* o = dissectObject(c, identifier);
			c->currentClass = o->name;
			o->doc = filterDoc(c, c->doc);
			c->doc = "";
			if(mode == MAVEN_ONLY_MAP)
				pushObject(c, findNamespaceID(c, c->currentNamespace), o);
			closeClass = true;
		} else if(prelim == "do") {
			if(mode == MAVEN_ONLY_COMPILE) {
				writeAutoCPPLine(c, "do {");
				close += "}";
			}
		} else if(prelim == "if") {
			if(mode == MAVEN_ONLY_COMPILE) {
				keywordIf(c, identifier, close);
			}
		} else if(prelim == "enum") {
			// nothing here
		} else if(prelim == "else") {
			if(mode == MAVEN_ONLY_COMPILE) {
				keywordElse(c, identifier, close);
			}
		} else if(prelim == "for") {
			if(mode == MAVEN_ONLY_COMPILE) {
				keywordFor(c, identifier, close);
			}
		} else if(prelim == "while") {
			if(mode == MAVEN_ONLY_COMPILE) {
				keywordWhile(c, identifier, close);
			}
		} else if(prelim == "try") {
			if(mode == MAVEN_ONLY_COMPILE) {
				writeAutoCPPLine(c, "try {");
				close += "}";
			}
		} else if(prelim == "switch") {
			if(mode == MAVEN_ONLY_COMPILE) {
				int actionStart;
				StringList types;
				MavenMutability mut;
				c->switchArgument = dissectCode(c, getStatementQuestion(identifier, actionStart), types, mut);
				// bug #17: check switchArgument is not invalid
				writeAutoCPPLine(c, "if(false) {");
				close += "}";
				closeSwitch = true;
			}
		} else if(prelim == "catch") {
			if(mode == MAVEN_ONLY_COMPILE) {
				MavenVariable catchVar;
				writeAutoCPPLine(c, keywordCatch(c, identifier, catchVar) + " {");
				pushLocalScope(c, catchVar);
				close += "}";
			}
		} else if(prelim == "with") {
			// bug #18: with() can not be nested
			// bug #19: make sure object is valid
			int namespaceID, objectID;
			bool isLocal;
			resolveVariable(c, identifier.substr(identifier.find('(') + 1, identifier.find(')') -
												 identifier.find('(') - 1), c->withObject,
												 namespaceID, objectID, isLocal, false);
			closeWith = true;
		} else if(isRegisteringFunction(c, identifier)) {
			// bug #20: abc() { } looks like a function
			MavenFunction func = dissectFunction(c, identifier);
			c->currentFunction = func.name;
			closeFunction = true;
			if(mode == MAVEN_ONLY_COMPILE) {
				writeCPPLine(c, string("} namespace ") + c->currentNamespace + "{");
				writeCPPLine(c, func.getCPPLine(c, c->currentClass) + "{");
				
				// if this is a constructor we have to init the super
				if(func.name == c->currentClass)
					writeCPPLine(c, "super(\"" + c->currentNamespace + "." + c->currentClass + "\");");
				close = "}";
				
				// add arguments to localScope
				for(int i = 0; i < func.args.length(); ++i)
					pushLocalScope(c, func.args[i]);
			}
			
			if(mode == MAVEN_ONLY_MAP) {
				func.doc = filterDoc(c, c->doc);
				pushFunction(c, findNamespaceID(c, c->currentNamespace),
							 findObjectID(c, findNamespaceID(c, c->currentNamespace), c->currentClass), func);
				c->doc = "";
			}
		} else if(isRegisteringVariable(c, smartTokens(identifier))) {
			if(mode == MAVEN_ONLY_MAP) {
				// use the substr to take off the '=' from the end
				registerVariable(c, smartTokens(identifier.substr(0, identifier.length() - 1)), false, var);
			}
		} else {
			pushError(c, "Unknown block identifier '%s' in '%s'", trim(prelim), identifier);
			return;
		}
	}
}
