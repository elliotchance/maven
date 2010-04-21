#ifndef MAVENCORE_MAVEN_EXCEPTION
#define MAVENCORE_MAVEN_EXCEPTION 1

#include "../mavencoreclean.h"

namespace maven {
	
	class Exception extends maven::Object {
		public_variable maven::String* reason;
		public_variable maven_int line;
		public_variable maven::String* file;
		public_variable maven_long errorCode;
		
		public_constructor Exception();
		
		public_method maven::String* description();
	};
	
}

#endif
