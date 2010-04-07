#ifndef MAVENCORE_MAVEN_STRING
#define MAVENCORE_MAVEN_STRING 1

#include "mavencore.h"

namespace maven {
	
	class Data;
	
	class String {
		// these are internal and hidden from maven
		public_variable maven_byte* s;
		public_variable maven_int len;
		public_variable String(const maven_byte* newString);
		
		// constrctors
		public_constructor String();
		
		// manipulation
		public_method maven::String* append(maven::String* str);
		public_method void erase();
		public_method maven::String* substring(maven_int length);
		public_method maven::String* substring(maven_int start, maven_int length);
		
		// searching
		public_method maven_int indexOf(maven::String* otherString);
		
		// testing
		public_method maven_int compare(maven::String* otherString);
		public_method maven_boolean isEmpty();
		public_method maven_int length();
		
		// type conversion
		public_method maven_boolean toBoolean();
		public_method maven_byte toByte();
		public_method maven_char toCharacter();
		public_method maven::Data* toData();
		public_method maven_double toDouble();
		public_method maven_float toFloat();
		public_method maven_int toInteger();
		public_method maven_long toLong();
		public_method maven_quad toQuad();
		public_method maven_short toShort();
		public_method maven::String* toString();
		
		public_static_method maven::String* valueOf(maven_boolean value);
		public_static_method maven::String* valueOf(maven_byte value);
		public_static_method maven::String* valueOf(maven_char value);
		public_static_method maven::String* valueOf(maven_double value);
		public_static_method maven::String* valueOf(maven_float value);
		public_static_method maven::String* valueOf(maven_int value);
		public_static_method maven::String* valueOf(maven_long value);
		public_static_method maven::String* valueOf(maven_quad value);
		public_static_method maven::String* valueOf(maven_short value);
		
		// misc
		public_method maven_int levenshtein(maven::String* otherString);
		
		// hashes
		public_method maven::String* md5();
		public_method maven::String* sha1();
		
		// operators
		public_method maven::String* operator_plus(maven::String* str2);
		public_method maven::String* operator_plus(maven_quad str2);
		public_method maven_boolean operator_equal(maven::String* str2);
	};
	
}

#endif
