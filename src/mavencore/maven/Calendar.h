#ifndef MAVENCORE_MAVEN_CALENDAR
#define MAVENCORE_MAVEN_CALENDAR 1

#include "../mavencoreclean.h"
#include "../maven/Date.h"

namespace maven {
	
	class Calendar extends maven::Object {
		public_constructor Calendar();
		
		public_static_method maven_int epochSeconds();
		public_static_method maven_int epochDays();
		public_static_method maven::Date* now();
		public_static_method maven_double runtime();
	};
	
}

#endif
