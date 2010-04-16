/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_operators.h"

int findFunctionID(MavenCompiler* c, int namespaceID, int objectID, string function, MavenVariables args, bool strict) {
	if(namespaceID < 0 || objectID < 0) return -1;
	bool match = false;
	
	// because function can be overloaded with multiple interchangable types
	// we try to first see if there is an exact match
	for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++i) {
		if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name == function &&
		   c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).args.length() == args.length()) {
			match = true;
			for(int j = 0; j < args.length(); ++j) {
				if(!canCastBetween(c, args[j].type,
								   c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).args[j].type, true, true)) {
					match = false;
					break;
				}
			}
			if(match) return i;
		}
	}
	
	// ok not so strict now
	if(!strict) {
		for(int i = 0; i < c->namespaces->at(namespaceID).objects->at(objectID)->functions->length(); ++i) {
			if(c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).name == function &&
			   c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).args.length() == args.length()) {
				match = true;
				for(int j = 0; j < args.length(); ++j) {
					if(!canCastBetween(c, args[j].type, c->namespaces->at(namespaceID).objects->at(objectID)->functions->at(i).args[j].type, false, true)) {
						match = false;
						break;
					}
				}
				if(match) return i;
			}
		}
	}
	
	// can't find a suitable match
	return -1;
}
