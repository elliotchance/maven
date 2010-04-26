/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_DOC_H
#define _MAVEN_DOC_H 1

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "struct_MavenDocTag.h"
#include "struct_MavenFunction.h"
#include "struct_MavenVariable.h"

MavenDocTag filterDoc(MavenCompiler* c, string comment);
void generateHTMLMethodTags(ofstream& file, MavenFunction f);
void generateHTMLVariableTags(ofstream& file, MavenVariable f);
void generateHTMLHeader(ofstream& file, string extraBodyAttributes = "");
void generateHTMLFooter(ofstream& file);
int  countNonInheritedVariables(MavenObject o);
int  countConstructors(MavenObject o);
int  countOperatorMethods(MavenObject o);
int  countNonInheritedNormalMethods(MavenObject o);
void generateHTMLMethodWords(ofstream& file, MavenFunction f);
void generateHTML(MavenCompiler* c);
void generateSQL(MavenCompiler* c);
void generateSQLite3(MavenCompiler* c);
void generateXML(MavenCompiler* c);
string sqlSafe(string str);
string sqlSafe(bool b);
string generateHTMLCommentTag(MavenCompiler* c, string input);
string colourHTMLCode(MavenCompiler* c, string input);

#endif
