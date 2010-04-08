/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "doc.h"

using namespace std;

/*
 <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
 <html xmlns="http://www.w3.org/1999/xhtml">
 <head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
 <title>Untitled Document</title>
 </head>
 
 <body>
 </body>
 </html>
*/ 

void generateHTML(MavenCompiler* c) {
	// create the folder
	cout << "creating folder " << endl;
	
	// handles
	ofstream sql;
	sql.open("docs.sql");
	
	// namespaces
	int globalID = 1;
	for(int i = 0; i < c->namespaces.length(); ++i) {
		int namespaceID = globalID++;
		sql
		<< "insert into namespaces (id, doc, namespaceName) values ("
		<< namespaceID << ","
		<< sqlSafe(c->namespaces[i].doc) << ","
		<< sqlSafe(c->namespaces[i].name) << ");" << endl;
		
		for(int j = 0; j < c->namespaces[i].objects.length(); ++j) {
			int classID = globalID++;
			sql
			<< "insert into classes (id, pid, lineNumber, doc, className, isAbstract, isFinal, extendsClasses) values ("
			<< classID << ","
			<< namespaceID << ","
			<< c->namespaces[i].objects[j].line << ","
			<< sqlSafe(c->namespaces[i].objects[j].doc) << ","
			<< sqlSafe(c->namespaces[i].objects[j].name) << ","
			<< sqlSafe(c->namespaces[i].objects[j].isAbstract) << ","
			<< sqlSafe(c->namespaces[i].objects[j].isFinal) << ","
			<< sqlSafe(c->namespaces[i].objects[j].extends)
			<< ");" << endl;
			
			// variables
			for(int k = 0; k < c->namespaces[i].objects[j].variables.length(); ++k) {
				sql << "insert into variables (id, pid, lineNumber, doc, type, variableName, isPublic, isStatic) values ("
				<< globalID++ << ","
				<< classID << ","
				<< c->namespaces[i].objects[j].variables[k].atLine << ","
				<< sqlSafe(c->namespaces[i].objects[j].variables[k].doc) << ","
				<< sqlSafe(c->namespaces[i].objects[j].variables[k].type) << ","
				<< sqlSafe(c->namespaces[i].objects[j].variables[k].name) << ","
				<< sqlSafe(c->namespaces[i].objects[j].variables[k].isPublic) << ","
				<< sqlSafe(c->namespaces[i].objects[j].variables[k].isStatic)
				<< ");" << endl;
			}
			
			// functions
			for(int k = 0; k < c->namespaces[i].objects[j].functions.length(); ++k) {
				sql << "insert into functions (id, pid, lineNumber, doc, returnType, functionName, isPublic, isStatic, isExternal, alias, isAliasSystem, arguments) values ("
				<< globalID++ << ","
				<< classID << ","
				<< c->namespaces[i].objects[j].functions[k].atLine << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].doc) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].returnType) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].name) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].isPublic) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].isStatic) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].isExternal) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].alias) << ","
				<< sqlSafe(c->namespaces[i].objects[j].functions[k].alias_system) << ",";
				
				string arguments = "";
				for(int l = 0; l < c->namespaces[i].objects[j].functions[k].args.length(); ++l) {
					if(l) arguments += ", ";
					arguments += c->namespaces[i].objects[j].functions[k].args[l].type + " "
					+ c->namespaces[i].objects[j].functions[k].args[l].name;
				}
				sql << sqlSafe(arguments)
				<< ");" << endl;
			}
		}
	}
}
