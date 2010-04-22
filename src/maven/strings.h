/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRINGS_H
#define _MAVEN_STRINGS_H 1

#include "maven.h"
#include "struct_StringList.h"

bool startsWith(string a, string b);
StringList splitNested(string str);
StringList splitDots(string line);
StringList splitCommas(string line);
StringList split(char on, string line);
StringList split(string delimiters, string str);
StringList smartTokens(string line);
void skipWhitespace(string& str, int& cursor);
string padIntToString(int value, int size);
string intToString(int value);
string getLastEntity(string str);
string getFirstEntity(string str);
string escapeString(string c);
string combinePaths(string path1, string path2, bool includeLastSlash = true);
int charToInt(string c);
string boolOnOff(bool b);
string trim(string line);

#endif
