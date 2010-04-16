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
	for(int i = 0; i < c->namespaces->length(); ++i) {
		xml << "<namespace name=\"" << c->namespaces->at(i).name << "\">" << endl;
		xml << "  <doc><![CDATA[" << c->namespaces->at(i).doc.body << "]]></doc>" << endl;
		
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			xml << "  <class name=\"" << c->namespaces->at(i).objects->at(j)->name
			<< "\" line=\"" << c->namespaces->at(i).objects->at(j)->line << "\" isAbstract=\""
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->isAbstract) << "\" isFinal=\""
			<< sqlSafe(c->namespaces->at(i).objects->at(j)->isFinal) << "\">" << endl;
			xml << "    <doc><![CDATA[" << c->namespaces->at(i).objects->at(j)->doc.body << "]]></doc>" << endl;
			
			// variables
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
				xml << "    <variable type=\"" << c->namespaces->at(i).objects->at(j)->variables->at(k).type
				<< "\" name=\"" << c->namespaces->at(i).objects->at(j)->variables->at(k).name
				<< "\" line=\"" << c->namespaces->at(i).objects->at(j)->variables->at(k).atLine
				<< "\" isPublic=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).isPublic)
				<< "\" isStatic=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->variables->at(k).isStatic) << "\">" << endl;
				xml << "      <doc><![CDATA[" << c->namespaces->at(i).objects->at(j)->variables->at(k).doc.body << "]]></doc>" << endl;
				xml << "    </variable>" << endl;
			}
			
			// functions
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
				xml << "    <function returnType=\"" << c->namespaces->at(i).objects->at(j)->functions->at(k).returnType
				<< "\" name=\"" << c->namespaces->at(i).objects->at(j)->functions->at(k).name
				<< "\" line=\"" << c->namespaces->at(i).objects->at(j)->functions->at(k).atLine
				<< "\" isPublic=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isPublic)
				<< "\" isStatic=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isStatic)
				<< "\" isExternal=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).isExternal)
				<< "\" isAliasSystem=\"" << sqlSafe(c->namespaces->at(i).objects->at(j)->functions->at(k).alias_system)
				<< "\">" << endl;
				xml << "      <alias>" << c->namespaces->at(i).objects->at(j)->functions->at(k).alias << "</alias>" << endl;
				xml << "      <doc><![CDATA[" << c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body << "]]></doc>" << endl;
				xml << "      <arguments>" << endl;
				
				for(int l = 0; l < c->namespaces->at(i).objects->at(j)->functions->at(k).args.length(); ++l) {
					xml << "        <argument type=\"" << c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].type
						<< "\" name=\"" << c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].name << "\" />" << endl;
				}
				
				xml << "      </arguments>" << endl;
				xml << "    </function>" << endl;
			}
			
			// functions
			/*for(int k = 0; k < namespaces->at(i).objects->at(j)->functions.length(); ++k) {
			 << sqlSafe(namespaces->at(i).objects->at(j)->functions[k].alias) << ","
			 
			 string arguments = "";
			 for(int l = 0; l < namespaces->at(i).objects->at(j)->functions[k].args.length(); ++l) {
			 if(l) arguments += ", ";
			 arguments += namespaces->at(i).objects->at(j)->functions[k].args[l].type + " "
			 + namespaces->at(i).objects->at(j)->functions[k].args[l].name;
			 }
			 sql << sqlSafe(arguments)
			 << ");" << endl;
			 }*/
			xml << "  </class>" << endl;
		}
		xml << "</namespace>" << endl;
	}
}
