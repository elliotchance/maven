/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

void generateSQLite3(MavenCompiler* c) {
	// bug #33: build db
	system("rm -f docs.sqlite");
	system("cat docs.sql | sqlite3 docs.sqlite");
	//system("rm docs.sql");
}
