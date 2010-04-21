/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "enums.h"
#include "objects.h"
#include "constants.h"
#include "variables.h"

/**
 * This function tests if a given line (split into tokens) has the right components
 * to be registering a new variable.
 */
bool isRegisteringVariable(MavenCompiler* c, StringList tokens) {
	// what does it take to register a variable?
	// 1. must have a datatype.
	// 2. must not have brackets ().
	// 3. is allowed to have a default value, but be careful where its placed.
	// this function needs to be improved to work like dissectFunction()
	
	// skip other keywords
	int token;
	for(token = 0; token < tokens.length(); ++token)
		if(tokens[token] != "public" && tokens[token] != "private"
		   && tokens[token] != "static" && tokens[token] != "constant"
		   && tokens[token] != "readonly" && tokens[token] != "writeonly")
			break;
	
	// check data type
	string rawtype = stripRawType(tokens[token]);
	if(!isDataType(rawtype) && !objectExists(c, rawtype) && !enumExists(c, rawtype))
		return false;
	
	// the rest
	for(int i = 0; i < tokens.length(); ++i) {
		for(int j = 0; j < tokens[i].length(); ++j) {
			if(tokens[i][j] == '=') return true;
			if(tokens[i][j] == '(' || tokens[i][j] == ')')
				return false;
		}
	}
	
	return true;
}
