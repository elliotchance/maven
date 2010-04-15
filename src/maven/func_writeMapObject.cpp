/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_find.h"
#include "compiler_mapfile.h"

void writeMapObject(MavenCompiler* c, int namespaceID, int objectID) {
	c->mapFileHandle << "  // namespaceID: " << intToString(namespaceID)
					 << " objectID: " << intToString(objectID) << endl;
	
	// skip some internals
	if(c->namespaces[namespaceID].name == "maven")
		if(c->namespaces[namespaceID].objects[objectID].name == "Object" ||
		   c->namespaces[namespaceID].objects[objectID].name == "String" ||
		   c->namespaces[namespaceID].objects[objectID].name == "System" ||
		   c->namespaces[namespaceID].objects[objectID].name == "Selector" ||
		   c->namespaces[namespaceID].objects[objectID].name == "Array")
			return;
	
	// variables
	// C++ has a completely different way of dealing with static data members,
	// so it's easier to just stick the variables into a predictable namespace.
	if(countStaticVariables(c, namespaceID, objectID) > 0) {
		c->mapFileHandle << "  namespace " << c->namespaces[namespaceID].objects[objectID].name << "$static {" << endl;
		for(int k = 0; k < c->namespaces[namespaceID].objects[objectID].variables.length(); ++k) {
			if(!c->namespaces[namespaceID].objects[objectID].variables[k].isExternal &&
			   c->namespaces[namespaceID].objects[objectID].variables[k].isStatic) {
				c->mapFileHandle << "    static ";
				string type = findObjectPath(c, c->namespaces[namespaceID].objects[objectID].variables[k].type);
				if(type == MAVEN_INVALID)
					c->mapFileHandle << "int"; // this for an enum
				else c->mapFileHandle << type;
				c->mapFileHandle << " " << c->namespaces[namespaceID].objects[objectID].variables[k].name;
				if(c->namespaces[namespaceID].objects[objectID].variables[k].defaultValue != "")
					c->mapFileHandle << " = " << c->namespaces[namespaceID].objects[objectID].variables[k].defaultValue;
				c->mapFileHandle << ";" << endl;
			}
		}
		c->mapFileHandle << "  }\n";
	}
	
	if((c->namespaces[namespaceID].objects[objectID].variables.length() - countStaticVariables(c, namespaceID, objectID)) + countClassMethods(c, namespaceID, objectID) > 0) {
		c->mapFileHandle << "  class " << c->namespaces[namespaceID].objects[objectID].name;
		if(c->namespaces[namespaceID].objects[objectID].extends != "") {
			// classes can be extended by multiple classes, so lets split them up
			c->mapFileHandle << " : public ";
			StringList extendList = split(',', c->namespaces[namespaceID].objects[objectID].extends);
			c->mapFileHandle << findObjectPath(c, extendList[0], false);
			for(int ei = 1; ei < extendList.length(); ++ei)
				c->mapFileHandle << "," << findObjectPath(c, extendList[namespaceID], false);
		}
		c->mapFileHandle << " {" << endl;
		
		// non-static variable members
		for(int k = 0; k < c->namespaces[namespaceID].objects[objectID].variables.length(); ++k) {
			if(!c->namespaces[namespaceID].objects[objectID].variables[k].isStatic && !c->namespaces[namespaceID].objects[objectID].variables[k].isInherited) {
				c->mapFileHandle << "    ";
				if(c->namespaces[namespaceID].objects[objectID].variables[k].isPublic)
					c->mapFileHandle << "public: ";
				else c->mapFileHandle << "protected: ";
				string type = findObjectPath(c, c->namespaces[namespaceID].objects[objectID].variables[k].type);
				if(type == MAVEN_INVALID)
					c->mapFileHandle << "int"; // this for an enum
				else c->mapFileHandle << type;
				c->mapFileHandle << " " << c->namespaces[namespaceID].objects[objectID].variables[k].name;
				if(c->namespaces[namespaceID].objects[objectID].variables[k].defaultValue != "")
					c->mapFileHandle << " = " << c->namespaces[namespaceID].objects[objectID].variables[k].defaultValue;
				c->mapFileHandle << ";" << endl;
			}
		}
		
		// constructors, super() is injected into all constructors.
		MavenVariables args;
		if(findFunctionID(c, namespaceID, objectID, c->namespaces[namespaceID].objects[objectID].name, args, true) < 0) {
			c->mapFileHandle << "    public: " << c->namespaces[namespaceID].objects[objectID].name << "() { super(\"";
			c->mapFileHandle << c->namespaces[namespaceID].name << "." << c->namespaces[namespaceID].objects[objectID].name << "\"); } " << endl;
		}
		
		// methods
		for(int k = 0; k < c->namespaces[namespaceID].objects[objectID].functions.length(); ++k) {
			if(!c->namespaces[namespaceID].objects[objectID].functions[k].isExported && !c->namespaces[namespaceID].objects[objectID].functions[k].isInherited) {
				c->mapFileHandle << "    ";
				if(c->namespaces[namespaceID].objects[objectID].functions[k].isPublic)
					c->mapFileHandle << "public: ";
				else c->mapFileHandle << "protected: ";
				if(c->namespaces[namespaceID].objects[objectID].functions[k].isStatic)
					c->mapFileHandle << "static ";
				else if(c->namespaces[namespaceID].objects[objectID].functions[k].name !=
						c->namespaces[namespaceID].objects[objectID].name)
					c->mapFileHandle << "virtual ";
				
				if(c->namespaces[namespaceID].objects[objectID].functions[k].returnType != "<constructor>")
					c->mapFileHandle << findObjectPath(c, c->namespaces[namespaceID].objects[objectID].functions[k].returnType);
				
				// function arguments can't be static
				for(int i = 0; i < c->namespaces[namespaceID].objects[objectID].functions[k].args.length(); ++i)
					c->namespaces[namespaceID].objects[objectID].functions[k].args[i].isStatic = false;
				
				c->mapFileHandle << " " << c->namespaces[namespaceID].objects[objectID].functions[k].name << "(" << c->namespaces[namespaceID].objects[objectID].functions[k].args.getCPP(c) << ");" << endl;
			}
		}
		c->mapFileHandle << "  };\n";
	}
}
