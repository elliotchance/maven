/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "output.h"

void writeMapFile(MavenCompiler* c) {
	// we have to write the map of the map
	for(int i = 0; i < c->namespaces->length(); ++i) {
		c->mapFileHandle << "namespace " << c->namespaces->at(i).name << " {\n";
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j)
			//if((namespaces->at(i).objects[j]->variables.length() - countStaticVariables(i, j)) + countClassMethods(i, j) > 0)
				c->mapFileHandle << "  class " << c->namespaces->at(i).objects->at(j)->name << ";\n";
		c->mapFileHandle << "}\n";
	}
	
	// objects
	for(int i = 0; i < c->discovery.size(); ++i) {
		c->mapFileHandle << "namespace " << c->namespaces->at(c->discovery[i].namespaceID).name << " {" << endl;
		writeMapObject(c, c->discovery[i].namespaceID, c->discovery[i].objectID);
		c->mapFileHandle << "}\n";
	}
	
	// prepare class from compilation
	c->imports.clear();
	c->lineNumber = 0;
	c->errors.clear();
}
