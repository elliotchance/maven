#ifndef MAVENCORE_MAVEN_SHORT
#define MAVENCORE_MAVEN_SHORT 1

#include "mavencoreclean.h"
#include "maven.Data.h"

namespace maven {

	class Short extends maven::Object {
		public_variable maven_short value;
		
		public_constructor Short();
		public_constructor Short(maven_short newValue);
		
		public_method maven::String* toString();
	};

}

#endif
