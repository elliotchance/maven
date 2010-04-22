#ifndef MAVENCORE_MAVEN_BOUNDSEXCEPTION
#define MAVENCORE_MAVEN_BOUNDSEXCEPTION 1

#include "../mavencore.h"
#include "../maven/Exception.h"

namespace maven {
	
	class BoundsException extends maven::Exception {
		public_constructor BoundsException();
		public_constructor BoundsException(maven::String* variable, maven::String* filename, mint occuredLine);
	};
	
}

#endif
