/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"

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
	error.file = c->currentFile;
	error.message = message;
	error.arg1 = arg1;
	error.arg2 = arg2;
	error.level = MAVEN_ERROR;
	c->errors.push(error);
	
	// pushError always returns false to make it easier to return an
	// error from another function
	return false;
}
