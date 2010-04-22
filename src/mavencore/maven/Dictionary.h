#ifndef MAVENCORE_MAVEN_DICTIONARY
#define MAVENCORE_MAVEN_DICTIONARY 1

#include "../mavencore.h"

namespace maven {
	
	struct DictionaryItem {
		maven::Object* key;
		maven::Object* value;
		DictionaryItem* next;
		
		DictionaryItem(maven::Object* _key, maven::Object* _value) {
			key = _key;
			value = _value;
			next = NULL;
		}
	};
	
	class Dictionary extends maven::Object {
		// these are internal and hidden from maven
		public_variable DictionaryItem* d;
		public_variable DictionaryItem* last;
		public_variable mint len;
		
		// visible methods
		public_constructor Dictionary();
		public_method mint length();
		public_method mboolean setValue(maven::Object* key, maven::Object* value);
		public_method maven::Object* getValue(maven::Object* key);
		public_method mboolean keyExists(maven::Object* key);
	};
	
}

#endif
