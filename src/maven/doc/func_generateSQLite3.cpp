/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"

using namespace std;

void generateSQLite3(MavenCompiler* c) {
	// bug #33: build db
	system("rm -f docs.sqlite");
	system("cat docs.sql | sqlite3 docs.sqlite");
	//system("rm docs.sql");
}
