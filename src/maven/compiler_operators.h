/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL bool   canCastBetween(MavenCompiler* c, string type1, string type2, bool strict = false, bool warn = true);
MAVEN_DECL bool   isAssignOperator(string type);
MAVEN_DECL bool   isComparisonOperator(string type);
MAVEN_DECL bool   isOperator(string type);
MAVEN_DECL bool   isOperatorPart(string type);
MAVEN_DECL bool   isUnaryOperator(string type);
MAVEN_DECL int    getDataTypePrecedence(string name);
MAVEN_DECL string validateOperator(MavenCompiler* c, string op, string type1, string type2, string& overloaded_function);
MAVEN_DECL bool   isBitwiseOperator(string type);
MAVEN_DECL string translateOperatorFunction(string f);
