#ifndef MAVENCORE_MAVEN_MATH
#define MAVENCORE_MAVEN_MATH 1

#include <cmath>

#include "../mavencoreclean.h"

// standard math functions

#define MAVEN_MATH_E  (maven_quad) 2.71828182845904523536
#define MAVEN_MATH_PI (maven_quad) 3.14159265358979323846

namespace maven {
	
	// the majority of the standard maven math functions are aliased to system functions
	// so theres no need to make more functions here

	class Math extends maven::Object {
		public_static_method maven_quad log2(maven_quad x);
		public_static_method maven_quad sq(maven_quad x);
		public_static_method maven_quad cbrt(maven_quad x);
		public_static_method maven_quad pow10(maven_quad x);
		public_static_method maven_quad round(maven_quad x);
		public_static_method maven_quad round(maven_quad x, maven_byte places);
		public_static_method maven_quad round(maven_quad x, maven_quad nearest, maven_int mode);
		public_static_method maven_quad sinh(maven_quad x);
		public_static_method maven_quad cosh(maven_quad x);
		public_static_method maven_quad tanh(maven_quad x);
		public_static_method maven_quad sec(maven_quad x);
		public_static_method maven_quad csc(maven_quad x);
		public_static_method maven_quad cot(maven_quad x);
		public_static_method maven_quad asinh(maven_quad x);
		public_static_method maven_quad acosh(maven_quad x);
		public_static_method maven_quad atanh(maven_quad x);
		public_static_method maven_quad asec(maven_quad x);
		public_static_method maven_quad acsc(maven_quad x);
		public_static_method maven_quad acot(maven_quad x);
		public_static_method maven_quad asech(maven_quad x);
		public_static_method maven_quad acsch(maven_quad x);
		public_static_method maven_quad acoth(maven_quad x);
		public_static_method maven_quad rad2deg(maven_quad x);
		public_static_method maven_quad deg2rad(maven_quad x);
		public_static_method maven_quad random();
		public_static_method maven_quad random(maven_quad max);
		public_static_method maven_quad random(maven_quad min, maven_quad max);
	};

}

#endif
