#ifndef MAVENCORE_MAVEN_CHARACTER
#define MAVENCORE_MAVEN_CHARACTER 1

#include "../mavencoreclean.h"
#include "../maven/Data.h"

namespace maven {

	class Character extends maven::Object {
		public_variable maven_char value;
		
		public_constructor Character();
		public_constructor Character(maven_char newValue);
		
		public_method maven::String* toString();
	};

}

#endif
