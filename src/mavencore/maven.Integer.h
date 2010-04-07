#ifndef MAVENCORE_MAVEN_INTEGER
#define MAVENCORE_MAVEN_INTEGER 1

#include "mavencoreclean.h"
#include "maven.Data.h"

namespace maven {

	class Integer extends maven::Object {
		public_variable maven_int value;
		
		public_constructor Integer();
		public_constructor Integer(maven_int newValue);
		
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
	};

}

#endif
