#ifndef MAVENCORE_MAVEN_LONG
#define MAVENCORE_MAVEN_LONG 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Long extends maven::Object {
		public_variable mlong value;
		
		public_constructor Long();
		public_constructor Long(mlong newValue);
		
		public_method maven::String* toString();
	};

}

#endif
