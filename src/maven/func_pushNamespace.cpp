/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_find.h"
#include "keywords.h"

void pushNamespace(MavenCompiler* c, string namespaceName) {
	c->currentNamespace = namespaceName;
	
	// because namespaces can popup multiple times, if a namespace exists just ignore
	if(findNamespaceID(c, namespaceName) < 0) {
		MavenNamespace* ns = new MavenNamespace();
		ns->name = namespaceName;
		
		// always push the nil class
		MavenObject* o = new MavenObject();
		o->name = MAVEN_BARE_CLASS;
		extendObject(c, o, "maven.Object");
		
		ns->objects->push(o);
		c->namespaces->push(ns);
	}
}
