#ifndef MAVENCORE_MAVEN_LONG
#define MAVENCORE_MAVEN_LONG 1

#include "mavencoreclean.h"
#include "maven.Data.h"

namespace maven {

	class Long extends maven::Object {
		public_variable maven_long value;
		
		public_constructor Long();
		public_constructor Long(maven_long newValue);
		
		public_method maven::String* toString();
	};

}

#endif
