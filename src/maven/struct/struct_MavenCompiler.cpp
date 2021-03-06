/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenNamespace.h"
#include "struct_MavenNamespaces.h"
#include "struct_MavenObject.h"
#include "keywords.h"
#include "files.h"
#include "compiler.h"

using namespace std;

MavenCompiler::MavenCompiler() {
	// start the timer
	start = clock();
	
	// these are super defaults, the defaults are read from the maven.ini file
	// before compiling.
	option_c = false;
	option_h = false;
	option_i = "";
	option_K = false;
	option_n = "";
	option_o = "0";
	option_r = false;
	option_s = 1;
	option_w = "";
	option_W = "";
	option_x = false;
	option_v = false;
	option_V = false;
	option_doc_sql = "";
	option_doc_sqlite3 = "";
	option_doc_xml = "";
	
	// user can't modify the following options
	option_base_path = "";
	
	// reserved words
	reservedWords.push("abstract");
	reservedWords.push("alias");
	reservedWords.push("auto");
	reservedWords.push("boolean");
	reservedWords.push("byte");
	reservedWords.push("char");
	reservedWords.push("class");
	reservedWords.push("constant");
	reservedWords.push("delete");
	reservedWords.push("do");
	reservedWords.push("double");
	reservedWords.push("enum");
	reservedWords.push("extends");
	reservedWords.push("external");
	reservedWords.push("false");
	reservedWords.push("final");
	reservedWords.push("float");
	reservedWords.push("for");
	reservedWords.push("foreach");
	reservedWords.push("if");
	reservedWords.push("import");
	reservedWords.push("int");
	reservedWords.push("into");
	reservedWords.push("long");
	reservedWords.push("namespace");
	reservedWords.push("new");
	reservedWords.push("nil");
	reservedWords.push("operator");
	reservedWords.push("private");
	reservedWords.push("public");
	reservedWords.push("quad");
	reservedWords.push("return");
	reservedWords.push("self");
	reservedWords.push("short");
	reservedWords.push("signed");
	reservedWords.push("static");
	reservedWords.push("true");
	reservedWords.push("unsigned");
	reservedWords.push("uses");
	reservedWords.push("void");
	reservedWords.push("while");
	reservedWords.push("with");
	
	// other preperation stuff
	lineNumber = 0;
	currentFunction = "";
	currentNamespace = MAVEN_BARE_NAMESPACE;
	currentClass = MAVEN_BARE_CLASS;
	currentFile = "";
	dissectDepth = 0;
	totalLines = 0;
	totalFiles = 0;
	UID = 1;
	currentDirectory = getCurrentDirectory();
	namespaces = new MavenNamespaces();
	imports = new StringList();
	
	MavenNamespace* n;
	MavenObject* o;
	
	// push the 'maven' namespace
	n = new MavenNamespace();
	n->name = "maven";
	namespaces->push(n);
	
	// we manually start the classes Object and String
	n = new MavenNamespace();
	
	o = new MavenObject();
	o->name = MAVEN_BARE_CLASS;
	namespaces->at(0).objects->push(o);
	
	o = new MavenObject();
	o->name = "Object";
	namespaces->at(0).objects->push(o);
	
	o = new MavenObject();
	o->name = "String";
	namespaces->at(0).objects->push(o);
	
	//extendObject(this, namespaces[0].objects[2], "maven.Object");
	
	// push the 'global' object/namespace
	n = new MavenNamespace();
	n->name = MAVEN_BARE_NAMESPACE;
	namespaces->push(n);
	
	o = new MavenObject();
	o->name = MAVEN_BARE_CLASS;
	namespaces->at(1).objects->push(o);
	extendObject(this, namespaces->at(1).objects->at(0), "maven.Object");
	
	// add discovery for forced classes
	discovery.push_back(MavenObjectDiscovery(0, 0));
	discovery.push_back(MavenObjectDiscovery(0, 1));
	discovery.push_back(MavenObjectDiscovery(1, 0));
	
	// initMaven
	pushEntryLine(this, "maven::initMaven();");
	
	// for global object safety check
	pushEntryLine(this, "try {");
}
