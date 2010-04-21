/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "errors.h"
#include "objects.h"

using namespace std;

void extendObject(MavenCompiler* c, MavenObject* o, string extendClass) {
	if(o->extends == "")
		o->extends = extendClass;
	else o->extends += "," + extendClass;
		
	int namespaceID = -1, objectID = -1;
	findClass(c, extendClass, namespaceID, objectID);
	
	// class must be found
	smartAssert(namespaceID >= 0);
	smartAssert(objectID >= 0);
	
	// abstract classes can only extend other abstract classes
	if(o->isAbstract && !c->namespaces->at(namespaceID).objects->at(objectID)->isAbstract &&
	   c->namespaces->at(namespaceID).objects->at(objectID)->name != "Object") {
		pushError(c, "Abstract class '%s' can not inherit from non-abstract '%s'", o->name,
				  c->namespaces->at(namespaceID).objects->at(objectID)->name);
		return;
	}
	
	// methods
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++i) {
		// skip special Object methods
		if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name == "copy" &&
		   c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).args.length() == 0)
			continue;
			
		MavenFunction f = c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i);
		f.isInherited = true;
		o->functions->push(f);
	}
	
	// variables
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++i) {
		MavenVariable v = c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(i);
		v.isInherited = true;
		o->variables->push(v);
	}
}
