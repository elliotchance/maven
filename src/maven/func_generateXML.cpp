/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "doc.h"

using namespace std;

void generateXML(MavenCompiler* c) {
	// handles
	ofstream xml;
	xml.open("docs.xml");
	
	// header
	xml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
	
	// namespaces
	for(int i = 0; i < c->namespaces.length(); ++i) {
		xml << "<namespace name=\"" << c->namespaces[i].name << "\">" << endl;
		xml << "  <doc><![CDATA[" << c->namespaces[i].doc << "]]></doc>" << endl;
		
		for(int j = 0; j < c->namespaces[i].objects.length(); ++j) {
			xml << "  <class name=\"" << c->namespaces[i].objects[j].name
			<< "\" line=\"" << c->namespaces[i].objects[j].line << "\" isAbstract=\""
			<< sqlSafe(c->namespaces[i].objects[j].isAbstract) << "\" isFinal=\""
			<< sqlSafe(c->namespaces[i].objects[j].isFinal) << "\">" << endl;
			xml << "    <doc><![CDATA[" << c->namespaces[i].objects[j].doc << "]]></doc>" << endl;
			
			// variables
			for(int k = 0; k < c->namespaces[i].objects[j].variables.length(); ++k) {
				xml << "    <variable type=\"" << c->namespaces[i].objects[j].variables[k].type
				<< "\" name=\"" << c->namespaces[i].objects[j].variables[k].name
				<< "\" line=\"" << c->namespaces[i].objects[j].variables[k].atLine
				<< "\" isPublic=\"" << sqlSafe(c->namespaces[i].objects[j].variables[k].isPublic)
				<< "\" isStatic=\"" << sqlSafe(c->namespaces[i].objects[j].variables[k].isStatic) << "\">" << endl;
				xml << "      <doc><![CDATA[" << c->namespaces[i].objects[j].variables[k].doc << "]]></doc>" << endl;
				xml << "    </variable>" << endl;
			}
			
			// functions
			for(int k = 0; k < c->namespaces[i].objects[j].functions.length(); ++k) {
				xml << "    <function returnType=\"" << c->namespaces[i].objects[j].functions[k].returnType
				<< "\" name=\"" << c->namespaces[i].objects[j].functions[k].name
				<< "\" line=\"" << c->namespaces[i].objects[j].functions[k].atLine
				<< "\" isPublic=\"" << sqlSafe(c->namespaces[i].objects[j].functions[k].isPublic)
				<< "\" isStatic=\"" << sqlSafe(c->namespaces[i].objects[j].functions[k].isStatic)
				<< "\" isExternal=\"" << sqlSafe(c->namespaces[i].objects[j].functions[k].isExternal)
				<< "\" isAliasSystem=\"" << sqlSafe(c->namespaces[i].objects[j].functions[k].alias_system)
				<< "\">" << endl;
				xml << "      <alias>" << c->namespaces[i].objects[j].functions[k].alias << "</alias>" << endl;
				xml << "      <doc><![CDATA[" << c->namespaces[i].objects[j].functions[k].doc << "]]></doc>" << endl;
				xml << "      <arguments>" << endl;
				
				for(int l = 0; l < c->namespaces[i].objects[j].functions[k].args.length(); ++l) {
					xml << "        <argument type=\"" << c->namespaces[i].objects[j].functions[k].args[l].type << "\" name=\"" <<
					c->namespaces[i].objects[j].functions[k].args[l].name << "\" />" << endl;
				}
				
				xml << "      </arguments>" << endl;
				xml << "    </function>" << endl;
			}
			
			// functions
			/*for(int k = 0; k < namespaces[i].objects[j].functions.length(); ++k) {
			 << sqlSafe(namespaces[i].objects[j].functions[k].alias) << ","
			 
			 string arguments = "";
			 for(int l = 0; l < namespaces[i].objects[j].functions[k].args.length(); ++l) {
			 if(l) arguments += ", ";
			 arguments += namespaces[i].objects[j].functions[k].args[l].type + " "
			 + namespaces[i].objects[j].functions[k].args[l].name;
			 }
			 sql << sqlSafe(arguments)
			 << ");" << endl;
			 }*/
			xml << "  </class>" << endl;
		}
		xml << "</namespace>" << endl;
	}
}
