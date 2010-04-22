#ifndef MAVENCORE_MAVEN_BOOLEAN
#define MAVENCORE_MAVEN_BOOLEAN 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Boolean extends maven::Object {
		public_variable mboolean value;
		
		public_constructor Boolean();
		public_constructor Boolean(mboolean newValue);
		
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
