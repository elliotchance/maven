/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_FILES_H
#define _MAVEN_FILES_H 1

#include "maven.h"
#include "struct_StringList.h"

bool fileExists(string path);
string getCurrentDirectory();
bool makeDirectory(string path);
StringList readDirectory(string path);
string removeExtension(string file);

#endif
