/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_errors.h"
#include "compiler_compilefile.h"
#include "compiler_find.h"
#include "compiler_push.h"
#include "compiler_gnu.h"
#include "compiler_mapfile.h"
#include "compiler_init.h"
#include "doc.h"
#include "installer.h"
#include "compiler_strings.h"

void printErrorsAndWarnings(MavenCompiler* c) {
	if(isErrors(c)) {
		printErrors(c);
		cout << "--- Compilation stopped due to errors" << endl;
		exit(1);
	}
	
	if(isWarnings(c))
		printWarnings(c);
}

int main(int argc, char** argv) {
    MavenCompiler* c = new MavenCompiler();
	c->binDirectory = combinePaths(c->currentDirectory, argv[0], false);
	c->binDirectory = c->binDirectory.substr(0, c->binDirectory.find_last_of('/'));
	
	// read INI file
	readINI(c);
	printErrorsAndWarnings(c);
	
	// might be an install
	if(argc > 1) {
		if(!strcmp(argv[1], "install")) {
			if(argc < 3) installerUsage();
			installPackage(c, argv[2]);
			exit(0);
		}
	}
	
	// this is where we need to read the special arguments
	// and send them to the compiler.
	processProgramArguments(c, argc, argv);
	
	init(c);
	mapLine(c, "import maven.Object");
	mapLine(c, "import maven.String");
	mapLine(c, "import maven.System");
	mapLine(c, "import maven.*");
	
	for(int i = 0; i < 1; ++i) {
		compileFile(c, c->option_n + ".mav", MAVEN_ONLY_MAP);
		printErrorsAndWarnings(c);
	}
	MavenVariable v;
	v.name = "System";
	v.type = "maven.System";
	v.defaultValue = "new maven::System()";
	v.isStatic = true;
	pushVariable(c, findNamespaceID(c, MAVEN_BARE_NAMESPACE),
				 findObjectID(c, findNamespaceID(c, MAVEN_BARE_NAMESPACE), MAVEN_BARE_CLASS), v);
	
	// ok now we can write the map file
	writeMapFile(c);
	
	compileLine(c, "import maven.Object");
	compileLine(c, "import maven.String");
	compileLine(c, "import maven.System");
	compileLine(c, "import maven.Data");
	compileLine(c, "import maven.Exception");
	compileLine(c, "import maven.*");
	for(int i = 0; i < 1; ++i) {
		compileFile(c, c->option_n + ".mav", MAVEN_ONLY_COMPILE);
		printErrorsAndWarnings(c);
	}
	
	// selectors
	for(int i = 0; i < c->selectors.size(); ++i)
#if MAVEN_OS == 1
		writeMapFileLine(c, "void* " + c->selectors[i] + "$selector(void* argv);");
#elif MAVEN_OS == 2
	writeMapFileLine(c, "t_long " + c->selectors[i] + "$selector(void* argv);");
#endif
	
	writeEntryPoint(c);
	finish(c);
	
	// generate documentation
	if(c->option_doc_sqlite3 != "") {
		generateSQL(c);
		generateSQLite3(c);
	} else if(c->option_doc_sql != "")
		generateSQL(c);
	else if(c->option_doc_xml != "")
		generateXML(c);
	else if(c->option_doc_html != "")
		generateHTML(c);
	
	// GNU Compile
	gnuCompile(c);
	
	// GNU Link
	gnuLink(c);
	
	// clean up
	if(!c->option_K)
		clean(c);
	
	// show compilation statistics
	if(c->option_r)
		printf("Compile successful (%d lines, %d files, %.2f seconds)\n",
			   c->totalLines, c->totalFiles, ((double) (clock() - c->start)) / (double) CLOCKS_PER_SEC);
	
	// execute after compilation
	if(c->option_e)
#if MAVEN_OS == 1
		if(c->option_n[0] == '/')
			system((string("\"") + c->option_n + "\"").c_str());
		else system((string("\"./") + c->option_n + "\"").c_str());
#elif MAVEN_OS == 2
		system((c->option_n + ".exe").c_str());
#endif
	
    return 0;
}
