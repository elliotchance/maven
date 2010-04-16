/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_find.h"
#include "compiler_errors.h"

using namespace std;

void extendObject(MavenCompiler* c, MavenObject& o, string extendClass) {
	if(o.extends == "")
		o.extends = extendClass;
	else o.extends += "," + extendClass;
		
	int namespaceID = -1, objectID = -1;
	findClass(c, extendClass, namespaceID, objectID);
	
	// abstract classes can only extend other abstract classes
	if(o.isAbstract && !c->namespaces[namespaceID].objects[objectID].isAbstract &&
	   c->namespaces[namespaceID].objects[objectID].name != "Object") {
		pushError(c, "Abstract class '%s' can not inherit from non-abstract '%s'", o.name,
				  c->namespaces[namespaceID].objects[objectID].name);
		return;
	}
	
	// methods
	for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].functions.length(); ++i) {
		// skip special Object methods
		if(c->namespaces[namespaceID].objects[objectID].functions[i].name == "copy" &&
		   c->namespaces[namespaceID].objects[objectID].functions[i].args.length() == 0)
			continue;
			
		MavenFunction f = c->namespaces[namespaceID].objects[objectID].functions[i];
		f.isInherited = true;
		o.functions.push(f);
	}
	
	// variables
	for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].variables.length(); ++i) {
		/*MavenVariable v = c->namespaces[namespaceID].objects[objectID].variables[i];
		v.isInherited = true;
		o.variables.push(v);*/
	}
}
