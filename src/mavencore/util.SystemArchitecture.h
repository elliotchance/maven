#ifndef MAVENCORE_UTIL_SYSTEMARCHITECTURE
#define MAVENCORE_UTIL_SYSTEMARCHITECTURE 1

#include "mavencoreclean.h"

// System architecture information

namespace util {

	class SystemArchitecture extends maven::Object {
		private_static_method maven_boolean CPUID(int Function, int bit, char reg);
		private_static_method int CPUID(int Function, char reg);
		
		public_static_method maven_boolean MMX();
		public_static_method maven_boolean SSE();
		public_static_method maven_boolean SSE2();
		public_static_method maven_boolean SSE3();
		public_static_method maven_boolean SSSE3();
		public_static_method maven_boolean SSE4A();
		public_static_method maven_boolean SSE41();
		public_static_method maven_boolean SSE42();
		public_static_method maven_boolean P16BATOMIC();
		public_static_method maven_boolean LONGMODE();
		public_static_method maven_boolean multiProcessorCapable();
		public_static_method maven_int     totalCores();
	};
	
}

#endif

