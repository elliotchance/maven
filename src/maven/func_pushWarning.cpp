/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"

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
	error.file = c->currentFile;
	error.message = message;
	error.arg1 = arg1;
	error.arg2 = arg2;
	error.level = MAVEN_WARNING;
	c->errors.push(error);
	
	// pushWarning always returns true to make it easier to return an
	// error from another function
	return true;
}
