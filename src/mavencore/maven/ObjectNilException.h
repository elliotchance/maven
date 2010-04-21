#ifndef MAVENCORE_MAVEN_OBJECTNILEXCEPTION
#define MAVENCORE_MAVEN_OBJECTNILEXCEPTION 1

#include "../mavencoreclean.h"
#include "../maven/Exception.h"

namespace maven {
	
	class ObjectNilException extends maven::Exception {
		public_constructor ObjectNilException();
		public_constructor ObjectNilException(maven::String* variable, maven::String* filename, maven_int occuredLine);
	};
	
}

#endif
