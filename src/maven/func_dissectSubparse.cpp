/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_constants.h"
#include "compiler_push.h"
#include "compiler_dissect.h"

/**
 
 This function takes an expression that could be anything from a simple keyword like
 'true' to a complex multidementional object access.
 
 The first thing this function will do is separate the expression on a '.' and
 proccess each element based on the previous.
 
 @returns b.processed
 
 */
string dissectSubparse(MavenCompiler* c, MavenDissectBlock& b, string nextOp, StringList argumentTypes, bool warn) {
	// clean up
	b.trim();
	b.mutability = MU_IMPOSSIBLE;
	
	// value keywords
	if(b.original == "nil") {
		b.types.setTypes("nil");
		b.processed = "0";
		return b.processed;
	}
	if(b.original == "true" || b.original == "false") {
		b.types.setTypes("boolean");
		b.processed = b.original;
		return b.processed;
	}
	
	// FIXME: maybe make this if into any keyword?
	if(b.original == "break" || b.original == "continue") {
		b.types.setTypes(MAVEN_INVALID);
		b.processed = b.original;
		return b.processed;
	}
	
	// because the dot can be misinterpreted for a class.method we need to check this first
	// it might be a constant
	if(isNumber(b.original)) {
		b.types.setTypes(getConstantType(b.original));
		b.processed = b.original;
		return "(" + b.types[0] + ")" + b.original;
	}
	
	// split expression
	StringList splitExpression = splitDots(b.original);
	MavenVariable v;
	//b.types.clear();
	//cout << "  '" << b.original << "' '" << b.types.join(",") << "'" << endl;
	for(int i = 0; i < splitExpression.length(); ++i) {
		dissectSubparseSingle(c, splitExpression[i], b.processed, b.types, b.mutability,
							  v, (i == (splitExpression.length() - 1)), nextOp, argumentTypes, warn);
		
		// make sure all the Objects are OK
		if(c->option_s > 0 && v.name != "" && !isDataType(v.type) &&
		   v.name.substr(0, 1) != "<" && v.type.substr(0, 1) != "<" &&
		   (i < (splitExpression.length() - 1)))
			pushObjectSafety(c, b.processed);
	}
	
	// apply the prefix and postfix unary operators
	if(b.unary != "")
		b.processed = "(" + b.unary + b.processed + ")";
	if(b.postunary != "")
		b.processed = "(" + b.processed + b.postunary + ")";
	
	return b.processed;
}
