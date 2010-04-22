#ifndef MAVENCORE_MAVEN_FLOAT
#define MAVENCORE_MAVEN_FLOAT 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Float extends maven::Object {
		public_variable mfloat value;
		
		public_constructor Float();
		public_constructor Float(mfloat newValue);
		
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
