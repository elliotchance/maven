/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

bool processInstallerLine(MavenCompiler* c, string line, string packageName) {
	// blank lines and comments are ignored
	if(line == "" || line[0] == '#') return true;
	
	// get line action
	string action = "";
	for(int i = 0; i < line.length(); ++i) {
		if(line[i] == ' ' || line[i] == '\t') {
			break;
		} else action += line[i];
	}
	
	// perform actions
	
	if(action == "install-import") {
		// make sure the maven path exists for the package
		StringList parts = split('.', line.substr(16, line.length() - 17));
		
		system((string(SYSTEM_MKDIR) + "\"" + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.import")) + parts.join("/", parts.length() - 2) + "\"").c_str());
	
		StringList importParts = split('.', line.substr(16, line.length() - 17));
		
		// remove old files
		string system = string(SYSTEM_RM) + "\"" + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.import")) + parts.join("/", parts.length() - 2) + "/" + importParts.join(".", importParts.length() - 2, importParts.length() - 1) + "\"";
		std::system(system.c_str());
		
		// move files to import/
		system = string(SYSTEM_CP) + "\"" + packageName + "/" + line.substr(16, line.length() - 17);
		system += string("\" \"") + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.import")) + parts.join("/", parts.length() - 2) + "/" + importParts.join(".", importParts.length() - 2, importParts.length() - 1) + "\"";
		std::system(system.c_str());
		return true;
	}
	
	if(action == "install-library") {
		string system = string(SYSTEM_CP) + "\"" + packageName + "/" + line.substr(17, line.length() - 18);
		system += string("\" \"") + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.lib")) + packageName + ".o\"";
		std::system(system.c_str());
		return true;
	}
	
	if(action == "print") {
		cout << escapeString(line.substr(7, line.length() - 8));
		return true;
	}
	
	if(action == "compile-lib-c") {
		string system = "gcc -w -c ";
		system += string("-I\"") + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.src")) + "mavencore/\" ";
		system += string("-I\"") + combinePaths(c->currentDirectory, packageName) + "\" ";
		StringList files = split(' ', line.substr(15, line.length() - 16));
		for(int i = 0; i < files.length(); ++i)
			system += "\"" + packageName + "/" + files[i] + "\" ";
		system += " -o \"" + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.lib")) + "/";
		system += removeExtension(line.substr(15, line.length() - 16)) + ".o\"";
		
		std::system(system.c_str());
		return true;
	}
	
	if(action == "compile-lib-cpp") {
		string system = "g++ -w -c ";
		system += string("-I\"") + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.src")) + "mavencore/\" ";
		system += string("-I\"") + combinePaths(c->currentDirectory, packageName) + "\" ";
		StringList files = split(' ', line.substr(17, line.length() - 18));
		for(int i = 0; i < files.length(); ++i)
			system += "\"" + packageName + "/" + files[i] + "\" ";
		system += " -o \"" + combinePaths(c->currentDirectory, c->iniFile.getKey("directories.lib")) + "/";
		system += removeExtension(line.substr(17, line.length() - 18)) + ".o\"";
		
		std::system(system.c_str());
		return true;
	}
	
	cout << endl << "--- Unknown install step '" << action << "'" << endl;
	return false;
}
