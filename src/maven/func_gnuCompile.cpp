/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

void gnuCompile(MavenCompiler* c) {
	// bug #55: get rid of precompiling?
	/*string cmd = string("g++ -c ");
	cmd += extraLibraries.join(" ") + " ";
	cmd += option_n + ".cpp -o " + option_n + ".o";*/
	
	string mavencorelib = combinePaths(c->binDirectory, c->iniFile.getKey("directories.lib")) + "libmavencore.a";
	string cmd = string("g++ -O3 ");
	for(int i = 0; i < c->extraLibraries.length(); ++i)
	 	cmd += string("\"") + trim(c->extraLibraries[i]) + "\" ";
	cmd += string("\"") + c->option_n + ".cpp\" \"" + mavencorelib + "\" -o \"" + c->option_n + "\"";
	
	//cout << "Debug: " << cmd << endl;
	system(cmd.c_str());
}
