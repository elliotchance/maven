/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL int           charToInt(string c);
MAVEN_DECL MavenVariable getCompilerVariable(MavenCompiler* c, string name);
MAVEN_DECL bool          isNumber(string test);
MAVEN_DECL string        getConstantType(string& test);
MAVEN_DECL bool          isString(string test);
MAVEN_DECL bool          isDataType(string type);
MAVEN_DECL bool          isReservedWord(MavenCompiler* c, string word);
