#ifndef MAVENCORE_MAVEN_MATH
#define MAVENCORE_MAVEN_MATH 1

#include <cmath>

#include "../mavencore.h"

// standard math functions

#define MAVEN_MATH_E  (mquad) 2.71828182845904523536
#define MAVEN_MATH_PI (mquad) 3.14159265358979323846

namespace maven {
	
	// the majority of the standard maven math functions are aliased to system functions
	// so theres no need to make more functions here

	class Math extends maven::Object {
		public_static_method mquad log2(mquad x);
		public_static_method mquad sq(mquad x);
		public_static_method mquad cbrt(mquad x);
		public_static_method mquad pow10(mquad x);
		public_static_method mquad round(mquad x);
		public_static_method mquad round(mquad x, mbyte places);
		public_static_method mquad round(mquad x, mquad nearest, mint mode);
		public_static_method mquad sinh(mquad x);
		public_static_method mquad cosh(mquad x);
		public_static_method mquad tanh(mquad x);
		public_static_method mquad sec(mquad x);
		public_static_method mquad csc(mquad x);
		public_static_method mquad cot(mquad x);
		public_static_method mquad asinh(mquad x);
		public_static_method mquad acosh(mquad x);
		public_static_method mquad atanh(mquad x);
		public_static_method mquad asec(mquad x);
		public_static_method mquad acsc(mquad x);
		public_static_method mquad acot(mquad x);
		public_static_method mquad asech(mquad x);
		public_static_method mquad acsch(mquad x);
		public_static_method mquad acoth(mquad x);
		public_static_method mquad rad2deg(mquad x);
		public_static_method mquad deg2rad(mquad x);
		public_static_method mquad random();
		public_static_method mquad random(mquad max);
		public_static_method mquad random(mquad min, mquad max);
	};

}

#endif
