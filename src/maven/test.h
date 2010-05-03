/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

void getRecursiveFiles(std::vector<string> &stack, string path);
int runTests(MavenCompiler* c);
