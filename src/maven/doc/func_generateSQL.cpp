/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "doc.h"

using namespace std;

void generateSQL(MavenCompiler* c) {
	// handles
	ofstream sql;
	sql.open("docs.sql");
	
	// create tables
	sql << "drop table if exists options;" << endl;
	sql << "create table options (" << endl
	<< "name varchar(255) not null primary key," << endl
	<< "value varchar(255));" << endl << endl;
	
	sql << "drop table if exists namespaces;" << endl;
	sql << "create table namespaces (" << endl
	<< "id int not null primary key," << endl
	<< "doc text," << endl
	<< "namespaceName varchar(255)" << endl
	<< ");" << endl << endl;
	
	sql << "drop table if exists classes;" << endl;
	sql << "create table classes (" << endl
	<< "id int not null primary key," << endl
	<< "pid int not null," << endl
	<< "lineNumber int," << endl
	<< "doc text," << endl
	<< "className varchar(255)," << endl
	<< "isAbstract boolean not null default 0," << endl
	<< "isFinal boolean not null default 0," << endl
	<< "extendsClasses varchar(255)" << endl
	<< ");" << endl << endl;
	
	sql << "drop table if exists variables;" << endl;
	sql << "create table variables (" << endl
	<< "id int not null primary key," << endl
	<< "pid int not null," << endl
	<< "lineNumber int," << endl
	<< "doc text," << endl
	<< "type varchar(255)," << endl
	<< "variableName varchar(255)," << endl
	<< "isPublic boolean not null default 0," << endl
	<< "isStatic boolean not null default 0" << endl
	<< ");" << endl << endl;
	
	sql << "drop table if exists functions;" << endl;
	sql << "create table functions (" << endl
	<< "id int not null primary key," << endl
	<< "pid int not null," << endl
	<< "lineNumber int," << endl
	<< "doc text," << endl
	<< "returnType varchar(255)," << endl
	<< "functionName varchar(255)," << endl
	<< "arguments text," << endl
	<< "isPublic boolean not null default 0," << endl
	<< "isStatic boolean not null default 0," << endl
	<< "isExternal boolean not null default 0," << endl
	<< "alias varchar(255)," << endl
	<< "isAliasSystem boolean not null default 0" << endl
	<< ");" << endl << endl;
	
	// some default records
	sql << "insert into options (name, value) values ('version', '1.0');" << endl << endl;
	
	// namespaces
	int globalID = 1;
	for(int i = 0; i < c->namespaces->length(); ++i) {
		int namespaceID = globalID++;
		sql
		<< "insert into namespaces (id, doc, namespaceName) values ("
		<< namespaceID << ","
		<< sqlSafe(c->namespaces->at(i).doc.body) << ","
		<< sqlSafe(c->namespaces->at(i).name) << ");" << endl;
		
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			int classID = globalID++;
			sql
			<< "insert into classes (id, pid, lineNumber, doc, className, isAbstract, isFinal, extendsClasses) values ("
			<< classID << ","
			<< namespaceID << ","
			<< c->namespaces->at(i).objects->at(j)->line << ","
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->doc.body) << ","
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->name) << ","
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->isAbstract) << ","
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->isFinal) << ","
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->extends)
			<< ");" << endl;
			
			// variables
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
				sql << "insert into variables (id, pid, lineNumber, doc, type, variableName, isPublic, isStatic) values ("
				<< globalID++ << ","
				<< classID << ","
				<< c->namespaces->at(i).objects->at(j)->variables->at(k).atLine << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).doc.body) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).type) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).name) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).isPublic) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).isStatic)
				<< ");" << endl;
			}
			
			// functions
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
				sql << "insert into functions (id, pid, lineNumber, doc, returnType, functionName, isPublic, isStatic, isExternal, alias, isAliasSystem, arguments) values ("
				<< globalID++ << ","
				<< classID << ","
				<< c->namespaces->at(i).objects->at(j)->functions->at(k).atLine << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).returnType) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).name) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isPublic) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isStatic) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isExternal) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).alias) << ","
				<< sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).alias_system) << ",";
				
				string arguments = "";
				for(int l = 0; l < c->namespaces->at(i).objects->at(j)->functions->at(k).args.length(); ++l) {
					if(l) arguments += ", ";
					arguments += c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].type + " "
					+ c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].name;
				}
				sql << sqlSafe(arguments)
				<< ");" << endl;
			}
		}
	}
}
