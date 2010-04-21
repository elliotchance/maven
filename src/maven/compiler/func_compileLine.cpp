/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_StringList.h"
#include "strings.h"
#include "output.h"
#include "keywords.h"
#include "compiler_functions.h"
#include "variables.h"
#include "compiler.h"
#include "objects.h"
#include "scope.h"

bool compileLine(MavenCompiler* c, string line) {
	line = trim(line);
	string temp = "";
	
	// ignore blank lines
	if(line == "") return true;
	
	// clear any line-based buffers
	c->objectCheck.clear();
	
	// get the preliminary keyword to see if we can quickly deal with it
	string prelim = "";
	for(int i = 0; i < line.length(); ++i) {
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '(') break;
		else prelim += line[i];
	}
	
	// an if statement
	string close = "";
	if(prelim == "if") {
		keywordIf(c, line, close);
		writeAutoCPPLine(c, close);
		return true;
	}
	if(prelim == "else") {
		keywordElse(c, line, close);
		writeAutoCPPLine(c, close);
		return true;
		
		/*StringList types;
		MavenMutability mut;
		c->beforeLine = "";
		writeAutoCPPLine(c, "else {" + dissectCode(c, trim(line).substr(4), types, mut, true) + ";}");
		return true;*/
	}
	
	// a loop
	if(prelim == "for") {
		keywordFor(c, line, close);
		writeAutoCPPLine(c, close);
		return true;
	}
	if(prelim == "while") {
		keywordWhile(c, line, close);
		writeAutoCPPLine(c, close);
		return true;
	}
	
	// external lines can be ignored becuase they were taken care of in the mapping phase
	if(prelim == "external") return true;
	
	// import another file
	if(prelim == "import") {
		string importpath = trim(line.substr(prelim.length(), line.length()));
		
		// we might need to import all
		if(importpath.find("*") != string::npos)
			return importAll(c, importpath, true);
		else {
			// attach a library
			includeLibraryIfExists(c, importpath);
		}
		
		string importlocation = locateImport(c, importpath);
		if(alreadyImported(c, importlocation))
			return true;
		
		string thisFile = c->currentFile;
		string thisNamespace = c->currentNamespace;
		int thisLine = c->lineNumber;
		c->imports.push_back(importlocation);
		compileFile(c, importlocation, MAVEN_ONLY_COMPILE);
		writeCPPLine(c, string("} namespace ") + thisNamespace + "{\n");
		return resetCurrent(c, thisFile, thisNamespace, thisLine);
	}
	
	// change the namespace
	if(prelim == "namespace") {
		string ns = trim(line.substr(prelim.length(), line.length()));
		if(c->currentNamespace != ns)
			writeCPPLine(c, "} namespace " + ns + "{\n");
		c->currentNamespace = ns;
		return true;
	}
	
	// return line
	if(prelim == "return") {
		writeCPPLine(c, objectCheckCPP(c) + keywordReturn(c, line) + ";");
		return true;
	}
	
	// this could be registering a new variable
	StringList tokens = smartTokens(line);
	if(isRegisteringVariable(c, tokens)) {
		MavenVariable var;
		registerVariable(c, tokens, true, var);
		return true;
	}
	
	// try to dissect it
	StringList types;
	MavenMutability m;
	string newLine = dissectCode(c, line, types, m);
	
	// pre check for all the objects
	newLine = objectCheckCPP(c) + newLine;
	
	if(c->beforeLine != "")
		writeAutoCPPLine(c, c->beforeLine);
	writeAutoCPPLine(c, newLine + ";");
	c->beforeLine = "";
	
	return true;
}
