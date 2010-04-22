#ifndef MAVENCORE_MAVEN_CHARACTER
#define MAVENCORE_MAVEN_CHARACTER 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Character extends maven::Object {
		public_variable mchar value;
		
		public_constructor Character();
		public_constructor Character(mchar newValue);
		
		public_method maven::String* toString();
	};

}

#endif
