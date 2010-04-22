/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "operators.h"
#include "constants.h"
#include "scope.h"
#include "objects.h"

string dissectCode(MavenCompiler* c, string fullcode, StringList& types, MavenMutability& mut, bool warn) {
	fullcode = trim(fullcode);
	if(fullcode.length() == 0)
		return "";
	
	// get preliminary word
	string prelim = "";
	for(int i = 0; i < fullcode.length(); ++i) {
		if(!isalnum(fullcode[i]))
			break;
		else prelim += fullcode[i];
	}
	
	if(prelim == "return")
		return "return " + dissectCode(c, fullcode.substr(7), types, mut, warn);
	
	if(prelim == "throw")
		return "throw " + dissectCode(c, fullcode.substr(6), types, mut, warn);
	
	MavenDissectBlock db;
	vector<MavenDissectBlock> dbs;
	StringList ops;
	string temp = "", superfinal = "";
	++c->dissectDepth;
	types.clear();
	
	// first we slice the entire code block
	StringList splitCode = splitCommas(fullcode);
	for(int a = 0; a < splitCode.length(); ++a) {
		string code = trim(splitCode[a]);
		int i = 0;
		
		// begin
		while(i < code.length()) {
			// prepare
			db.reset();
			
			// forceCast
			skipWhitespace(code, i);
			if(code[i] == '(') {
				// attemp to read a forced type, otherwise rollback
				int old_i = i;
				++i;
				for(; i < code.length(); ++i) {
					if(code[i] == ')') break;
					db.forceCast += code[i];
				}
				++i;
				
				// a forceCast can only contain certain characters
				db.forceCast = trim(db.forceCast);
				for(int j = 0; j < db.forceCast.length(); ++j) {
					if(!isalnum(db.forceCast[j]) && db.forceCast[j] != '.' && db.forceCast[j] != '_') {
						db.forceCast = "";
						break;
					}
				}
				
				// check if its a valid type do rollback
				if(!isDataType(db.forceCast) && !objectExists(c, db.forceCast)) {
					db.forceCast = "";
					i = old_i;
				} else db.forceCast = findMavenObjectPath(c, db.forceCast);
			}
			
			// characters are converted to their integer form
			skipWhitespace(code, i);
			if(code[i] == '\'') {
				string str = "";
				++i;
				for(; code[i] != '\''; ++i)
					str += code[i];
				db.original = "'" + str + "'";
				++i;
			
				// we can stop here if all we have to dissect is a charcater
				if(i >= code.length() - 1) {
					dbs.push_back(db);
					//ops.push("");
					break;
				}
			}
			
			// a String
			if(code[i] == '"') {
				// or possibly a String
				string str = "";
				++i;
				for(; i < code.length(); ++i) {
					if(code[i] == '"') break;
					else if(code[i] == '\\') {
						str += string("\\") + code[i + 1];
						++i;
					} else str += code[i];
				}
				db.original = "\"" + str + "\"";
				++i;
			}
			
			// read the unary operator
			if((i < code.length() - 1) && isOperatorPart(code.substr(i, 1)) && code[i] != '@') {
				// some operators are multiple characters, so read ahead
				for(; isOperatorPart(code.substr(i, 1)); ++i)
					db.unary += code[i];
				
				// if the unary operator is a '[' we have started a descriptive argument function call
				if(db.unary.length() > 0 && db.unary[0] == '[') {
					string descArgs = "";
					for(; i < code.length(); ++i) {
						if(code[i] == ']') break;
						descArgs += code[i];
					}
				}
				
				// validate unary operator
				if(!isUnaryOperator(db.unary)) {
					pushError(c, "Invalid unary operator '%s'", db.unary);
					return MAVEN_INVALID;
				}
				
				// if the unary operator is + or - its part of the bareword
				if(db.unary == "+" || db.unary == "-") {
					db.original += db.unary;
					db.unary = "";
				}
			}
			
			// read the expression
			skipWhitespace(code, i);
			int countBrackets = 0, countSquare = 0;
			for(; i < code.length(); ++i) {
				     if(code[i] == '(') ++countBrackets;
				else if(code[i] == ')') --countBrackets;
				else if(code[i] == '[') ++countSquare;
				else if(code[i] == ']') --countSquare;
				else if(code[i] == '"') {
					db.original += code[i++];
					for(; i < code.length(); ++i) {
						if(code[i] == '\\') {
							db.original += code[i++];
							db.original += code[i];
						} else if(code[i] == '"')
							break;
						else db.original += code[i];
					}
				} else if(isOperatorPart(code.substr(i, 1)) && !countBrackets && !countSquare && code[i] != '@')
					break;
				db.original += code[i];
			}
			
			// post unary operator
			skipWhitespace(code, i);
			if((i < code.length() - 1) && isOperatorPart(code.substr(i, 1))) {
				// some operators are multiple characters, so read ahead
				string unary = "";
				for(; isOperatorPart(code.substr(i, 1)); ++i)
					unary += code[i];
				
				// validate unary operator
				if(unary == "++" || unary == "--")
					db.postunary = unary;
				else i -= unary.length();
			}
			
			// at this point there can only be an operator to join the next MavenDissectBlock
			skipWhitespace(code, i);
			if(i >= code.length() - 1 || isOperatorPart(code.substr(i, 1))) {
				// some operators are multiple characters, so read ahead
				string op = "";
				for(; i < code.length() && isOperatorPart(code.substr(i, 1)); ++i)
					op += code[i];
				op = trim(op);
				
				// make sure its a real operator
				if(op != "" && !isOperator(op)) {
					pushError(c, "Unknown operator '%s'", op);
					return MAVEN_INVALID;
				}
				
				// if this is the last operator on the statement (nothing after it)
				// lets try and move it to the unary
				if(i >= code.length() - 1 && op != "") {
					if(!isUnaryOperator(op)) {
						pushError(c, "Invalid unary operator '%s'", op);
						types.push(MAVEN_INVALID);
						return MAVEN_INVALID;
					}
					db.unary = op;
				}
				
				// push the single onto the stack to deal with later
				db.trim();
				dbs.push_back(db);
				ops.push(op);
			} else {
				pushError(c, "Operator expected after '%s' '%s'", code, code.substr(i, code.length() - i));
				types.push(MAVEN_INVALID);
				return MAVEN_INVALID;
			}
		}
		
		// bug #23: big problem?
		if(dbs.size() == 0)
			break;
		
		// make sure the number of operators matches the number of blocks
		if(ops.length() < dbs.size())
			ops.push("");
		
		// process each subparse and deal with the operators
		dissectSubparse(c, dbs[0], ops[0], types, warn);
		StringList types2;
		types2.setTypes(dbs[0].types.join(","));
		string final = dbs[0].processed;
		for(int i = 1; i < dbs.size(); ++i) {
			dissectSubparse(c, dbs[i], ops[i], types, warn);
			string overloadedfunction = "";
			types2.setTypes(validateOperator(c, ops[i - 1], types2.join(","),
											 dbs[i].types.join(","), overloadedfunction));
			if(overloadedfunction != "")
				final += "->" + overloadedfunction + "(" + dbs[i].processed + ")";
			else final += ops[i - 1] + " " + dbs[i].processed;
		}
		
		// reset and append final
		dbs.clear();
		ops.clear();
		
		if(superfinal != "")
			superfinal += ",";
		superfinal += "(" + final + ")";
		types.push(types2.join(","));
	}
	--c->dissectDepth;
	
	// all done
	return superfinal;
}
