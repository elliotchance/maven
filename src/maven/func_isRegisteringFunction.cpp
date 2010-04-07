/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

/**
 * This function tests if a given line (split into tokens) has the right components
 * to be a function definition.
 */
bool isRegisteringFunction(MavenCompiler* c, string line) {
	// what does it take to register a function?
	// 1. must have brackets ()
	StringList tokens = smartTokens(line);
	
	// external always makes it a function
	if(tokens[0] == "external")
		return true;
	
	// skip other keywords
	int token;
	for(token = 0; token < tokens.length(); ++token)
		if(tokens[token] != "public" && tokens[token] != "private" && tokens[token] != "static")
			break;
	
	// the rest
	for(int i = 0; i < tokens.length(); ++i)
		for(int j = 0; j < tokens[i].length(); ++j)
			if(tokens[i][j] == '(')
				return true;
	
	// didn't hit a '(' must be something else
	return false;
}
