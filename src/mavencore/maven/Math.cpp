#include "Math.h"

// standard math functions

namespace maven {
	
	// the majority of the standard maven math functions are aliased to system functions
	// so theres no need to make more functions here
	
	mquad Math::log2(mquad x) {
		return std::log(x) / std::log(2.0);
	}
	
	mquad Math::sq(mquad x) {
		return x * x;
	}
	
	mquad Math::cbrt(mquad x) {
		return pow(x, (mquad) 0.3333333333333333333);
	}
	
	mquad Math::pow10(mquad x) {
		return std::pow(10, x);
	}
	
	mquad Math::round(mquad x) {
		return round(x, 1, 0);
	}
	
	mquad Math::round(mquad x, mbyte places) {
		return round(x, pow(0.1, places), 0);
	}
	
	mquad Math::round(mquad x, mquad nearest, mint mode) {
		mquad rem = std::fmod(x, nearest);
		if(mode < 0) return (x - rem);
		if(mode > 0) return (x + (nearest - rem));
		if(rem >= (nearest * 0.5)) return (x + (nearest - rem));
		return (x - rem);
	}
	
	mquad Math::sinh(mquad x) {
		return ((std::pow(MAVEN_MATH_E, x) - std::pow(MAVEN_MATH_E, -x)) / 2);
	}
	
	mquad Math::cosh(mquad x) {
		return ((std::pow(MAVEN_MATH_E, x) + std::pow(MAVEN_MATH_E, -x)) / 2);
	}
	
	mquad Math::tanh(mquad x) {
		return (sinh(x) / cosh(x));
	}
	
	mquad Math::sec(mquad x) {
		return (1.0 / std::cos(x));
	}
	
	mquad Math::csc(mquad x) {
		return (1.0 / std::sin(x));
	}
	
	mquad Math::cot(mquad x) {
		return (1.0 / std::tan(x));
	}
	
	mquad Math::asinh(mquad x) {
		return (std::log(x + std::pow((std::pow(x, (mquad) 2.0) + 1.0), (mquad) 0.5)));
	}
	
	mquad Math::acosh(mquad x) {
		return (std::log(x + std::pow((std::pow(x, (mquad) 2.0) - 1.0), (mquad) 0.5)));
	}
	
	mquad Math::atanh(mquad x) {
		return (0.5 * std::log((1.0 + x) / (1.0 - x)));
	}
	
	mquad Math::asec(mquad x) {
		return (1.0 / std::acos(x));
	}
	
	mquad Math::acsc(mquad x) {
		return (1.0 / std::asin(x));
	}
	
	mquad Math::acot(mquad x) {
		return (1.0 / std::atan(x));
	}
	
	mquad Math::asech(mquad x) {
		return (1.0 / acosh(x));
	}
	
	mquad Math::acsch(mquad x) {
		return (1.0 / asinh(x));
	}
	
	mquad Math::acoth(mquad x) {
		return (1.0 / atanh(x));
	}
	
	mquad Math::deg2rad(mquad x) {
		return (x * (MAVEN_MATH_PI / 180.0));
	}
	
	mquad Math::rad2deg(mquad x) {
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
	
	mquad Math::random(mquad min, mquad max) {
		return fmod(genrand(), max - min) + min;
	}
	
	mquad Math::random(mquad max) {
		return fmod(genrand(), max);
	}
	
	mquad Math::random() {
		return genrand() / 4294967295.0;
	}

}
