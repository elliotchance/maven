/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL string     boolOnOff(bool b);
MAVEN_DECL string     escapeString(string c);
MAVEN_DECL void       stripHyphen(string& key, string& value);
MAVEN_DECL bool       startsWith(string a, string b);
MAVEN_DECL StringList splitCommas(string line);
MAVEN_DECL StringList splitDots(string line);
MAVEN_DECL StringList split(char on, string line);
MAVEN_DECL StringList split(string delimiters, string str);
MAVEN_DECL StringList smartTokens(string line);
MAVEN_DECL string     trim(string line);
MAVEN_DECL string     getLastEntity(string str);
MAVEN_DECL string     getFirstEntity(string str);
MAVEN_DECL string     getStatementQuestion(string line, int& actionStart);
MAVEN_DECL string     intToString(int value);
MAVEN_DECL string     padIntToString(int value, int size);
MAVEN_DECL string     combinePaths(string path1, string path2, bool includeLastSlash = true);
MAVEN_DECL string     getCurrentDirectory();
MAVEN_DECL void       skipWhitespace(string& str, int& cursor);
MAVEN_DECL string     nativeToObject(string type);
MAVEN_DECL string     processScalarString(string in, bool warn);
MAVEN_DECL string     removeExtension(string file);
