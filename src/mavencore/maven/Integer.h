#ifndef MAVENCORE_MAVEN_INTEGER
#define MAVENCORE_MAVEN_INTEGER 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Integer extends maven::Object {
		public_variable mint value;
		
		public_constructor Integer();
		public_constructor Integer(mint newValue);
		
		public_method mboolean toBoolean();
		public_method mbyte toByte();
		public_method mchar toCharacter();
		public_method maven::Data* toData();
		public_method mdouble toDouble();
		public_method mfloat toFloat();
		public_method mint toInteger();
		public_method mlong toLong();
		public_method mquad toQuad();
		public_method mshort toShort();
		public_method maven::String* toString();
	};

}

#endif
