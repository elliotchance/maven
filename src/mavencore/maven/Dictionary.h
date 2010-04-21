#ifndef MAVENCORE_MAVEN_DICTIONARY
#define MAVENCORE_MAVEN_DICTIONARY 1

#include "../mavencoreclean.h"

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
		public_variable maven_int len;
		
		// visible methods
		public_constructor Dictionary();
		public_method maven_int length();
		public_method maven_boolean setValue(maven::Object* key, maven::Object* value);
		public_method maven::Object* getValue(maven::Object* key);
		public_method maven_boolean keyExists(maven::Object* key);
	};
	
}

#endif
