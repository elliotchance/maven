#include "Math.h"

// standard math functions

namespace maven {
	
	// the majority of the standard maven math functions are aliased to system functions
	// so theres no need to make more functions here
	
	maven_quad Math::log2(maven_quad x) {
		return std::log(x) / std::log(2.0);
	}
	
	maven_quad Math::sq(maven_quad x) {
		return x * x;
	}
	
	maven_quad Math::cbrt(maven_quad x) {
		return pow(x, (maven_quad) 0.3333333333333333333);
	}
	
	maven_quad Math::pow10(maven_quad x) {
		return std::pow(10, x);
	}
	
	maven_quad Math::round(maven_quad x) {
		return round(x, 1, 0);
	}
	
	maven_quad Math::round(maven_quad x, maven_byte places) {
		return round(x, pow(0.1, places), 0);
	}
	
	maven_quad Math::round(maven_quad x, maven_quad nearest, maven_int mode) {
		maven_quad rem = std::fmod(x, nearest);
		if(mode < 0) return (x - rem);
		if(mode > 0) return (x + (nearest - rem));
		if(rem >= (nearest * 0.5)) return (x + (nearest - rem));
		return (x - rem);
	}
	
	maven_quad Math::sinh(maven_quad x) {
		return ((std::pow(MAVEN_MATH_E, x) - std::pow(MAVEN_MATH_E, -x)) / 2);
	}
	
	maven_quad Math::cosh(maven_quad x) {
		return ((std::pow(MAVEN_MATH_E, x) + std::pow(MAVEN_MATH_E, -x)) / 2);
	}
	
	maven_quad Math::tanh(maven_quad x) {
		return (sinh(x) / cosh(x));
	}
	
	maven_quad Math::sec(maven_quad x) {
		return (1.0 / std::cos(x));
	}
	
	maven_quad Math::csc(maven_quad x) {
		return (1.0 / std::sin(x));
	}
	
	maven_quad Math::cot(maven_quad x) {
		return (1.0 / std::tan(x));
	}
	
	maven_quad Math::asinh(maven_quad x) {
		return (std::log(x + std::pow((std::pow(x, (maven_quad) 2.0) + 1.0), (maven_quad) 0.5)));
	}
	
	maven_quad Math::acosh(maven_quad x) {
		return (std::log(x + std::pow((std::pow(x, (maven_quad) 2.0) - 1.0), (maven_quad) 0.5)));
	}
	
	maven_quad Math::atanh(maven_quad x) {
		return (0.5 * std::log((1.0 + x) / (1.0 - x)));
	}
	
	maven_quad Math::asec(maven_quad x) {
		return (1.0 / std::acos(x));
	}
	
	maven_quad Math::acsc(maven_quad x) {
		return (1.0 / std::asin(x));
	}
	
	maven_quad Math::acot(maven_quad x) {
		return (1.0 / std::atan(x));
	}
	
	maven_quad Math::asech(maven_quad x) {
		return (1.0 / acosh(x));
	}
	
	maven_quad Math::acsch(maven_quad x) {
		return (1.0 / asinh(x));
	}
	
	maven_quad Math::acoth(maven_quad x) {
		return (1.0 / atanh(x));
	}
	
	maven_quad Math::deg2rad(maven_quad x) {
		return (x * (MAVEN_MATH_PI / 180.0));
	}
	
	maven_quad Math::rad2deg(maven_quad x) {
		return (x * (180.0 / MAVEN_MATH_PI));
	}
	
	unsigned int genrand() {
		// Random number generator using MT19937 algorithm
		unsigned long y;
		static unsigned long mag01[2] = {0x0UL, MATRIX_A};
		/* mag01[x] = x * MATRIX_A  for x=0,1 */
		
		if(mti >= N) { /* generate N words at one time */
			int kk;
			
			for (kk=0;kk<N-M;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			for (;kk<N-1;kk++) {
				y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
				mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
			
			mti = 0;
		}
		
		y = mt[mti++];
		
		/* Tempering */
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);
		
		return y;
	}
	
	maven_quad Math::random(maven_quad min, maven_quad max) {
		return fmod(genrand(), max - min) + min;
	}
	
	maven_quad Math::random(maven_quad max) {
		return fmod(genrand(), max);
	}
	
	maven_quad Math::random() {
		return genrand() / 4294967295.0;
	}

}
