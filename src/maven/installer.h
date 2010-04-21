/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_INSTALLER_H
#define _MAVEN_INSTALLER_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"

bool processInstallerLine(MavenCompiler* c, string line, string packageName);
bool installPackage(MavenCompiler* c, string package);
void installerUsage();
string findPackage(string package);

#endif
