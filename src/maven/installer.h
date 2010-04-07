/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

string     findPackage(string package);
void       installerUsage();
bool       installPackage(MavenCompiler* c, string package);
bool       processInstallerLine(MavenCompiler* c, string line, string packageName);
StringList readDirectory(string path);
