#ifndef MAVENCORE_MAVEN_DATE
#define MAVENCORE_MAVEN_DATE 1

#include "mavencoreclean.h"

namespace maven {
	
	class Date extends maven::Object {
		public_variable maven_short year;
		public_variable maven_byte month;
		public_variable maven_byte day;
		public_variable maven_byte hour;
		public_variable maven_byte minute;
		public_variable maven_byte second;
		
		public_constructor Date();
	};
	
}

#endif
