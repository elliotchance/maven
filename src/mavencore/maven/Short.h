#ifndef MAVENCORE_MAVEN_SHORT
#define MAVENCORE_MAVEN_SHORT 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace maven {

	class Short extends maven::Object {
		public_variable mshort value;
		
		public_constructor Short();
		public_constructor Short(mshort newValue);
		
		public_method maven::String* toString();
	};

}

#endif
