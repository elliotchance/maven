/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

// doc.cpp
string sqlSafe(bool b);
string sqlSafe(string str);
string filterDoc(MavenCompiler* c, string comment);

// doc_sql.cpp
void generateSQL(MavenCompiler* c);

// doc_sqlite3.cpp
void generateSQLite3(MavenCompiler* c);

// doc_xml.cpp
void generateXML(MavenCompiler* c);
