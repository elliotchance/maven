/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"
#include "enum_MavenQuotes.h"

StringList splitCommas(string line) {
	StringList r;
	string token = "";
	MavenQuotes inQuotes = MQ_NONE;
	int bracketCount = 0;
	for(int i = 0; i < line.length(); ++i) {
		// bracket counting
		if(line[i] == '(') ++bracketCount;
		else if(line[i] == ')') --bracketCount;
		
		// quotes
		if(line[i] == '\'' && (i == 0 || line[i - 1] != '\\')) {
			if(inQuotes == MQ_NONE) inQuotes = MQ_SINGLE;
			else inQuotes = MQ_NONE;
		}
		if(line[i] == '"' && (i == 0 || line[i - 1] != '\\')) {
			if(inQuotes == MQ_NONE) inQuotes = MQ_DOUBLE;
			else inQuotes = MQ_NONE;
		}
		
		// do split
		if(line[i] == ',' && inQuotes == MQ_NONE && !bracketCount) {
			token = trim(token);
			if(token.length()) r.push(token);
			token = "";
		} else token += line[i];
	}
	token = trim(token);
	if(token.length()) r.push(token);
	return r;
}
