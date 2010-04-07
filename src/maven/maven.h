/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#ifndef MAVEN_H
#define MAVEN_H 1

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
#include "structs.h"

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

/** this is placed before each function declaration */
#define MAVEN_DECL

#endif
