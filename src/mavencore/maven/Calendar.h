#ifndef MAVENCORE_MAVEN_CALENDAR
#define MAVENCORE_MAVEN_CALENDAR 1

#include "../mavencore.h"
#include "../maven/Date.h"

namespace maven {
	
	class Calendar extends maven::Object {
		public_constructor Calendar();
		
		public_static_method mint epochSeconds();
		public_static_method mint epochDays();
		public_static_method maven::Date* now();
		public_static_method mdouble runtime();
	};
	
}

#endif
