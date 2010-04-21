/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "errors.h"
#include "strings.h"

int findEnumElement(MavenCompiler *c, string entity, int& namespaceID, int& enumID) {
	namespaceID = -1;
	enumID = -1;
	
	// bug #41: enumtype.enumelement
	StringList parts = split('.', entity);
	if(parts.length() > 1) {
		// we dont have to check for ambiguous because for that to be true,
		// there would have to be multiple enums by the same name, but the
		// maven mapper will stop that
		for(int i = 0; i < c->namespaces->length(); ++i) {
			for(int j = 0; j < c->namespaces->at(i).enums.size(); ++j) {
				if(c->namespaces->at(i).enums[j].name == parts[0]) {
					for(int k = 0; k < c->namespaces->at(i).enums[j].items.size(); ++k) {
						if(c->namespaces->at(i).enums[j].items[k].name == parts[1]) {
							namespaceID = i;
							enumID = j;
							return k;
						}
					}
				}
			}
		}
		
		// couldn't find it
		return -1;
	}
	
	// we need to make sure it is not ambiguous
	int ambig_count = 0;
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).enums.size(); ++j) {
			for(int k = 0; k < c->namespaces->at(i).enums[j].items.size(); ++k) {
				if(c->namespaces->at(i).enums[j].items[k].name == entity)
					++ambig_count;
			}
		}
	}
	if(ambig_count > 1) {
		pushError(c, "Ambiguous enum element '%s'", entity);
		return -2;
	}
	
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).enums.size(); ++j) {
			for(int k = 0; k < c->namespaces->at(i).enums[j].items.size(); ++k) {
				if(c->namespaces->at(i).enums[j].items[k].name == entity) {
					namespaceID = i;
					enumID = j;
					return k;
				}
			}
		}
	}
	
	// couldn't find it
	return -1;
}
