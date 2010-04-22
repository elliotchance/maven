#ifndef MAVENCORE_MAVEN_DATE
#define MAVENCORE_MAVEN_DATE 1

#include "../mavencore.h"

namespace maven {
	
	class Date extends maven::Object {
		public_variable mshort year;
		public_variable mbyte month;
		public_variable mbyte day;
		public_variable mbyte hour;
		public_variable mbyte minute;
		public_variable mbyte second;
		
		public_constructor Date();
	};
	
}

#endif
