/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_CONSTANTS_H
#define _MAVEN_CONSTANTS_H 1

#include "maven.h"

bool isString(string test);
bool isNumber(string test);
bool isDataType(string type);
string getConstantType(string& test);

#endif
