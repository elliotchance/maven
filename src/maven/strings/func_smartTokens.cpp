/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"

StringList smartTokens(string line) {
	StringList list;
	string token;
	int bracketCount = 0;
	bool inQuotes = false;
	
	for(int i = 0; i < line.length(); ++i) {
		if(line[i] == '"') inQuotes = !inQuotes;
		if(line[i] == ' ' && bracketCount == 0) {
			token = trim(token);
			if(token.length() > 0) list.push(token);
			token = "";
		} else if(line[i] == '(') {
			if(inQuotes) token += '(';
			token = trim(token);
			if(token.length() > 0) list.push(token);
			++bracketCount;
			token = "";
		} else if(line[i] == ')') {
			if(inQuotes) token += ')';
			token = trim(token);
			list.push(string("(") + token + ")");
			--bracketCount;
			token = "";
		} else token += line[i];
	}
	token = trim(token);
	if(token.length() > 0) list.push(token);
	
	return list;
}
