/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_SCOPE_H
#define _MAVEN_SCOPE_H 1

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenDissectBlock.h"

string getStatementQuestion(string line, int& actionStart);
string findLocalScope(MavenCompiler* c, string name, MavenVariable& r);
string dissectSubparseSingle(MavenCompiler* c, string code, string& r, StringList& types,
							 MavenMutability& mut, MavenVariable& prev, bool lastSubparse,
							 string nextOp, StringList argumentTypes, bool warn);
string dissectSubparse(MavenCompiler* c, MavenDissectBlock& b, string nextOp,
					   StringList argumentTypes, bool warn);
void dissectIdentifer(MavenCompiler* c, string identifier, int mode, bool& closeFunction, bool& closeClass,
					  bool& closeSwitch, bool& closeWith, MavenVariable& var, string& close);
string dissectCodeSingle(MavenCompiler* c, string bareword, string entity, string element,
						 string args, string signature, string& type, MavenMutability& mut,
						 string nextop);
string dissectCode(MavenCompiler* c, string fullcode, StringList& types, MavenMutability& mut, bool warn = true);
bool compileBlock(MavenCompiler* c, string identifier, string code, int mode);
void pushLocalScope(MavenCompiler* c, MavenVariable var);

#endif
