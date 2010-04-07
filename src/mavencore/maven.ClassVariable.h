#ifndef MAVENCORE_MAVEN_CLASSVARIABLE
#define MAVENCORE_MAVEN_CLASSVARIABLE 1

#include "mavencoreclean.h"

namespace maven {
	
	class ClassVariable extends maven::Object {
		public_variable maven_boolean isPublic;
		public_variable maven::String* name;
		public_variable maven::String* type;
		
		public_constructor ClassVariable(maven_boolean _isPublic, maven::String* _name, maven::String* _type);
	};
	
}

#endif
