/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

MAVEN_DECL bool        enumExists(MavenCompiler* c, string name);
MAVEN_DECL vector<int> findClass(MavenCompiler* c, string entity, int& namespaceID, int& objectID);
MAVEN_DECL int         findEnumElement(MavenCompiler *c, string entity, int& namespaceID, int& enumID);
MAVEN_DECL int         findEnumID(MavenCompiler* c, int namespaceID, string enumName);
MAVEN_DECL int         findFunctionID(MavenCompiler* c, int namespaceID, int objectID, string function,
									  MavenVariables args, bool strict = false);
MAVEN_DECL string      findFunctionPath(MavenCompiler* c, string entity, MavenVariables args,
										int& namespaceID, int& objectID, int& funcID);
MAVEN_DECL string      findLocalScope(MavenCompiler* c, string name, MavenVariable& r);
MAVEN_DECL string      findMavenEnumPath(MavenCompiler* c, string entity);
MAVEN_DECL string      findMavenObjectPath(MavenCompiler* c, string entity);
MAVEN_DECL int         findObjectID(MavenCompiler* c, int namespaceID, string objectName);
MAVEN_DECL string      findObjectPath(MavenCompiler* c, string entity, bool includePointer = true);
MAVEN_DECL string      findVariablePath(MavenCompiler* c, string entity, int& namespaceID, int& objectID,
										int& variableID);
MAVEN_DECL int         findNamespaceID(MavenCompiler* c, string namespaceName);
MAVEN_DECL int         findVariableID(MavenCompiler* c, int namespaceID, int objectID, string variable);
MAVEN_DECL bool        objectExists(MavenCompiler* c, string name);
