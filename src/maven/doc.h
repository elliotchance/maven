/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

string      sqlSafe(bool b);
string      sqlSafe(string str);
MavenDocTag filterDoc(MavenCompiler* c, string comment);
void        generateSQL(MavenCompiler* c);
void        generateSQLite3(MavenCompiler* c);
void        generateXML(MavenCompiler* c);
void        generateHTML(MavenCompiler* c);
void        printAllNamespaces(MavenCompiler* c);
