/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_MAVEN_H
#define _MAVEN_MAVEN_H 1

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "config.h"

using namespace std;

#define MAVEN_COMPILER_VERSION 1000000
#define MAVEN_COMPILER_NAME    "genesis"
#define MAVEN_WARNING          1
#define MAVEN_ERROR            2
#define MAVEN_BARE_NAMESPACE   "global"
#define MAVEN_BARE_CLASS       "nil"
#define MAVEN_INVALID          "<invalid>"
#define MAVEN_AMBIGUOUS        "<ambiguous>"
#define MAVEN_ONLY_MAP         1
#define MAVEN_ONLY_COMPILE     2
#define MAVEN_LOCALSCOPE       1000000

#define smartAssert(e) \
	if(!(e)) { \
		printf("Assertion Failed: %s\n", #e); \
		printf("            File: %s\n", __FILE__); \
		printf("        Function: %s\n", __PRETTY_FUNCTION__); \
		printf("            Line: %d\n", __LINE__); \
		exit(1); \
	}

#define smartAssertMessage(e, fmt, ...) \
	if(!(e)) { \
		printf("Assertion Failed: %s\n", #e); \
		printf("            File: %s\n", __FILE__); \
		printf("        Function: %s\n", __PRETTY_FUNCTION__); \
		printf("            Line: %d\n", __LINE__); \
		printf("         Message: "); \
		printf(fmt, __VA_ARGS__); \
		printf("\n"); \
		exit(1); \
	}

/**
 * This is placed before each function declaration.
 */
#define MAVEN_DECL

#endif
