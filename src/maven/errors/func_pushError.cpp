/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "errors.h"
#include "strings.h"

bool pushError(MavenCompiler* c, string message) {
	pushError(c, message, "", "");
	
	// pushError always returns false to make it easier to return an
	// error from another function
	return false;
}

bool pushError(MavenCompiler* c, string message, string arg) {
	pushError(c, message, arg, "");
	
	// pushError always returns false to make it easier to return an
	// error from another function
	return false;
}

bool pushError(MavenCompiler* c, string message, string arg1, string arg2) {
	MavenError error;
	error.line = c->lineNumber;
	error.file = combinePaths(c->currentDirectory, c->currentFile, false);
	error.message = message;
	error.arg1 = arg1;
	error.arg2 = arg2;
	error.level = MAVEN_ERROR;
	c->errors.push(error);
	
	// pushError always returns false to make it easier to return an
	// error from another function
	return false;
}
