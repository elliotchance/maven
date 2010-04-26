/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "scope.h"
#include "compiler.h"

bool compileFile(MavenCompiler* c, string file, int mode) {
	// prepare
	ifstream infile;
	infile.open(file.c_str());
	if(!infile.is_open())
		return false;
	c->filesParsed.push(file);

	// remember position
	string cFile = c->currentFile;
	string cNamespace = c->currentNamespace;
	int cLine = ++c->lineNumber;
	++c->totalFiles;
	c->currentFile = file;
	
	// read whole file
	string wholeFile = "";
	while(!infile.eof())
		wholeFile += infile.get();
	infile.close();
	
	bool r = compileBlock(c, "", wholeFile, mode);
	
	// restore position
	resetCurrent(c, cFile, cNamespace, cLine);
	
	return r;
}
