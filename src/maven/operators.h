/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_OPERATORS_H
#define _MAVEN_OPERATORS_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

bool isComparisonOperator(string type);
string validateOperator(MavenCompiler* c, string op, string type1, string type2, string& overloaded_function);
string translateOperatorFunction(string f);
bool isUnaryOperator(string type);
bool isOperatorPart(string type);
bool isOperator(string type);
bool isBitwiseOperator(string type);
bool isAssignOperator(string type);
int getDataTypePrecedence(string name);
bool canCastBetween(MavenCompiler* c, string type1, string type2, bool strict = false, bool warn = true);
string translateOperator(string op);
bool isObjectOperator(string type);

#endif
