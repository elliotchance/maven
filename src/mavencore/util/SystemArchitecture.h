#ifndef MAVENCORE_UTIL_SYSTEMARCHITECTURE
#define MAVENCORE_UTIL_SYSTEMARCHITECTURE 1

#include <bitset>

#include "../mavencore.h"

// System architecture information

namespace util {

	class SystemArchitecture extends maven::Object {
		private_static_method mboolean CPUID(int Function, int bit, char reg);
		private_static_method int CPUID(int Function, char reg);
		
		public_static_method mboolean MMX();
		public_static_method mboolean SSE();
		public_static_method mboolean SSE2();
		public_static_method mboolean SSE3();
		public_static_method mboolean SSSE3();
		public_static_method mboolean SSE4A();
		public_static_method mboolean SSE41();
		public_static_method mboolean SSE42();
		public_static_method mboolean P16BATOMIC();
		public_static_method mboolean LONGMODE();
		public_static_method mboolean multiProcessorCapable();
		public_static_method mint totalCores();
	};
	
}

#endif

