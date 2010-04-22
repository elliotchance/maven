/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "strings.h"
#include "objects.h"
#include "functions.h"
#include "variables.h"
#include "output.h"

void writeMapObject(MavenCompiler* c, int namespaceID, int objectID) {
	c->mapFileHandle << "  // namespaceID: " << intToString(namespaceID)
					 << " objectID: " << intToString(objectID) << endl;
	
	// skip some internals
	if(c->namespaces->at(namespaceID).name == "maven")
		if(c->namespaces->at(namespaceID).objects->at(objectID)->name == "Object" ||
		   c->namespaces->at(namespaceID).objects->at(objectID)->name == "String" ||
		   c->namespaces->at(namespaceID).objects->at(objectID)->name == "System" ||
		   c->namespaces->at(namespaceID).objects->at(objectID)->name == "Selector" ||
		   c->namespaces->at(namespaceID).objects->at(objectID)->name == "Array")
			return;
	
	// variables
	// C++ has a completely different way of dealing with static data members,
	// so it's easier to just stick the variables into a predictable namespace.
	if(countStaticVariables(c, namespaceID, objectID) > 0) {
		c->mapFileHandle << "  namespace " << c->namespaces->at(namespaceID).objects->at(objectID)->name
		                 << "$static {" << endl;
		for(int k = 0; k < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++k) {
			if(!c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isExternal &&
			   c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isStatic) {
				c->mapFileHandle << "    static ";
				string type = cType(findObjectPath(c, c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).type));
				if(type == MAVEN_INVALID)
					c->mapFileHandle << "int"; // this for an enum
				else c->mapFileHandle << type;
				c->mapFileHandle << " " << c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).name;
				if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).defaultValue != "")
					c->mapFileHandle << " = " <<
					  c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).defaultValue;
				c->mapFileHandle << ";" << endl;
			}
		}
		c->mapFileHandle << "  }\n";
	}
	
	if((c->namespaces->at(namespaceID).objects->at(objectID)->variables->length() -
		countStaticVariables(c, namespaceID, objectID)) + countClassMethods(c, namespaceID, objectID) > 0) {
		c->mapFileHandle << "  class " << c->namespaces->at(namespaceID).objects->at(objectID)->name;
		if(c->namespaces->at(namespaceID).objects->at(objectID)->extends != "") {
			// classes can be extended by multiple classes, so lets split them up
			c->mapFileHandle << " : public ";
			StringList extendList = split(',', c->namespaces->at(namespaceID).objects->at(objectID)->extends);
			c->mapFileHandle << cType(findObjectPath(c, extendList[0], false));
			for(int ei = 1; ei < extendList.length(); ++ei)
				c->mapFileHandle << "," << cType(findObjectPath(c, extendList[namespaceID], false));
		}
		c->mapFileHandle << " {" << endl;
		
		// non-static variable members
		for(int k = 0; k < c->namespaces->at(namespaceID).objects->at(objectID)->variables->length(); ++k) {
			if(!c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isStatic &&
			   !c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isInherited) {
				c->mapFileHandle << "    ";
				if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).isPublic)
					c->mapFileHandle << "public: ";
				else c->mapFileHandle << "protected: ";
				string type = cType(findObjectPath(c, c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).type));
				if(type == MAVEN_INVALID)
					c->mapFileHandle << "int"; // this for an enum
				else c->mapFileHandle << type;
				c->mapFileHandle << " " << c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).name;
				if(c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).defaultValue != "")
					c->mapFileHandle << " = " << c->namespaces->at(namespaceID).objects->at(objectID)->variables->at(k).defaultValue;
				c->mapFileHandle << ";" << endl;
			}
		}
		
		// constructors, super() is injected into all constructors.
		MavenVariables args;
		if(findFunctionID(c, namespaceID, objectID, c->namespaces->at(namespaceID).objects->at(objectID)->name, args, true) < 0) {
			c->mapFileHandle << "    public: " << c->namespaces->at(namespaceID).objects->at(objectID)->name << "() { super(\"";
			c->mapFileHandle << c->namespaces->at(namespaceID).name << "." << c->namespaces->at(namespaceID).objects->at(objectID)->name << "\"); } " << endl;
		}
		
		// methods
		for(int k = 0; k < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++k) {
			if(!c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).isExported &&
			   !c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).isInherited) {
				c->mapFileHandle << "    ";
				if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).isPublic)
					c->mapFileHandle << "public: ";
				else c->mapFileHandle << "protected: ";
				if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).isStatic)
					c->mapFileHandle << "static ";
				else if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).name !=
						c->namespaces->at(namespaceID).objects->at(objectID)->name)
					c->mapFileHandle << "virtual ";
				
				if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).returnType != "<constructor>")
					c->mapFileHandle << cType(findObjectPath(c, c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).returnType));
				
				// function arguments can't be static
				for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).args.length(); ++i)
					c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).args[i].isStatic = false;
				
				c->mapFileHandle << " " << c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).name << "("
								<< c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(k).args.getCPP(c) << ");" << endl;
			}
		}
		c->mapFileHandle << "  };\n";
	}
}
