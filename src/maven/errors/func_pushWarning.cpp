/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "errors.h"
#include "strings.h"

bool pushWarning(MavenCompiler* c, string message) {
	pushWarning(c, message, "", "");
	
	// pushWarning always returns true to make it easier to return an
	// error from another function
	return true;
}

bool pushWarning(MavenCompiler* c, string message, string arg) {
	pushWarning(c, message, arg, "");
	
	// pushWarning always returns true to make it easier to return an
	// error from another function
	return true;
}

bool pushWarning(MavenCompiler* c, string message, string arg1, string arg2) {
	MavenError error;
	error.line = c->lineNumber;
	error.file = combinePaths(c->currentDirectory, c->currentFile, false);
	error.message = message;
	error.arg1 = arg1;
	error.arg2 = arg2;
	error.level = MAVEN_WARNING;
	c->errors.push(error);
	
	// pushWarning always returns true to make it easier to return an
	// error from another function
	return true;
}
