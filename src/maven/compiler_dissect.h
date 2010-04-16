/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL string         buildLine(MavenCompiler* c, string bareword, string entity, string args);
MAVEN_DECL MavenFunction  dissectFunction(MavenCompiler* c, string line);
MAVEN_DECL void           dissectIdentifer(MavenCompiler* c, string identifier, int mode, bool& closeFunction,
										   bool& closeClass, bool& closeSwitch, bool& closeWith,
										   MavenVariable& var, string& close);
MAVEN_DECL MavenVariable  dissectVariable(MavenCompiler* c, string line);
MAVEN_DECL MavenObject*   dissectObject(MavenCompiler* c, string line);
MAVEN_DECL MavenVariables dissectArguments(MavenCompiler* c, string line);
MAVEN_DECL void           dissectCodeArguments(MavenCompiler* c, string& rawargs, string& blocktype);
MAVEN_DECL string         dissectCode(MavenCompiler* c, string fullcode, StringList& types, MavenMutability& mut,
									  bool warn = true);
MAVEN_DECL string         dissectCodeSingle(MavenCompiler* c, string bareword, string entity, string element,
											string args, string signature, string& type, MavenMutability& mut,
											string nextop = "");
MAVEN_DECL string         dissectSubparse(MavenCompiler* c, MavenDissectBlock& b, string nextOp,
										  StringList argumentTypes, bool warn);
MAVEN_DECL string         dissectSubparseSingle(MavenCompiler* c, string code, string& r, StringList& types,
												MavenMutability& mut, MavenVariable& prev, bool lastSubparse,
												string nextOp, StringList argumentTypes, bool warn);
