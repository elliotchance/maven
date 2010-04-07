/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_init.h"
#include "installer.h"

bool installPackage(MavenCompiler* c, string package) {
	// look for the package
	cout << "Looking for " << package << "... ";
	string packagePath = findPackage(package);
	
	if(packagePath == "") {
		cout << "Unknown package '" << package << "'" << endl;
		return false;
	}
	cout << "Found" << endl;
	
	// if its online download it
	if(packagePath.length() > 7 && packagePath.substr(0, 7) == "http://") {
		cout << "Downloading " << packagePath << "... ";
		cout << "Done" << endl;
	}
	
	// uncompress if required
	if(packagePath.length() > 4 && packagePath.substr(packagePath.length() - 4, 4) == ".zip") {
		cout << "Uncompressing " << packagePath << "... ";
#if MAVEN_OS == 1
		system((string("unzip -u ") + packagePath + " > /dev/null").c_str());
#else
		system((string("unzip -qq -o ") + packagePath).c_str());
#endif
		cout << "Done" << endl;
	}
	
	// look for the installer script
	ifstream installFile;
	installFile.open((package + "/" + package + ".installer").c_str(), ios::in);
	if(!installFile.is_open())
		die("Could not find installer file");
	
	// run the installer script
	string line = "", heading = "";
	bool foundOS = false;
	while(!installFile.eof()) {
		char ch = installFile.get();
		if(ch == '\n' || ch == '\r') {
			line = trim(line);
			if(line.length() > 0 && line[0] == '[') {
				heading = line.substr(1, line.length() - 2);
				if(heading == "other") foundOS = true;
			} else if(heading == "other") {
				if(!processInstallerLine(c, line, package))
					exit(1);
			}
			line = "";
		} else line += ch;
	}
	
	if(!foundOS)
		die("This package is not available for your operating system.");
	
	// install was successful
	return true;
}
