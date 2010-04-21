/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "errors.h"
#include "namespaces.h"
#include "constants.h"

using namespace std;

bool keywordEnum(MavenCompiler* c, string identifier, string code) {
	identifier = trim(identifier);
	code = trim(code);
	MavenEnum e;
	
	// get the enum name
	e.name = trim(identifier.substr(4, identifier.length() - 4));

	// bug #30: make sure the enum doesn't already exist
	for(int i = 0; i < c->namespaces->at(findNamespaceID(c, c->currentNamespace)).enums.size(); ++i) {
		if(c->namespaces->at(findNamespaceID(c, c->currentNamespace)).enums[i].name == e.name) {
			pushError(c, "Enum '%s' already defined", e.name);
			return false;
		}
	}
	
	// split and process the items
	StringList elements = splitCommas(code);
	if(trim(code) == "") {
		pushError(c, "The enum '%s' must be defined with at least 1 element", e.name);
		return false;
	}
	
	for(int i = 0; i < elements.length(); ++i) {
		// bug #31: get the 'default'
		MavenEnumItem item;
		
		StringList parts = split('=', elements[i]);
		
		// check if this is a default item
		string itemname = trim(parts[0]);
		if(itemname.length() > 7 && itemname.substr(0, 7) == "default") {
			// make sure there is only 1 default item
			for(int j = 0; j < e.items.size(); ++j) {
				if(e.items[j].isDefault) {
					pushError(c, "There may only be 1 default element in the enum '%s'", e.name);
					return false;
				}
			}
			
			item.isDefault = true;
			itemname = trim(itemname.substr(7, itemname.length() - 7));
		}
		
		// make sure the item doesn't already exist
		for(int j = 0; j < e.items.size(); ++j) {
			if(e.items[j].name == itemname) {
				pushError(c, "Duplicate element name %s in enum %s", itemname, e.name);
				return false;
			}
		}
		item.name = itemname;
		
		// get the manual value
		if(parts.length() > 1) {
			string p = trim(parts[1]);
			
			// make sure the manual value is in an acceptable format
			if(isNumber(p) || p == "true" || p == "false") {
				string type = getConstantType(p);
				if(type != "int" && type != "boolean")
					pushWarning(c, "Non-int in manual value for enum element '%s.%s'", e.name, item.name);
				
				if(p == "true") item.value = 1;
				else if(p == "false") item.value = 0;
				else item.value = atoi(p.c_str());
			} else if(p.length() > 2 && p[0] == '\'' && p[p.length() - 1] == '\'') {
				item.value = charToInt(p.substr(1, p.length() - 2));
			} else {
				pushError(c, "Invalid manual value for enum element '%s.%s', must be int", e.name, item.name);
				return false;
			}
		} else item.value = i;
		
		e.items.push_back(item);
	}
	
	// push whole enum
	c->namespaces->at(findNamespaceID(c, c->currentNamespace)).enums.push_back(e);
	
	return true;
}
