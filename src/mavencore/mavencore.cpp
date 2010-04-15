/*
 *  mavencore.cpp
 *  maven
 *
 *  Created by Elliot Chance on 15/05/09.
 *  Copyright 2009 Chance MEDIA Pty Ltd. All rights reserved.
 *
 */

#include "mavencoreclean.h"

maven_long mt[N]; /* the array for the state vector  */
maven_int mti = N + 1; /* mti==N+1 means mt[N] is not initialized */

namespace maven {
	
	void multiarray() {
		// int myInts[][] = new int[5][10];
		objectArray* myInts = new objectArray(5);
		for(int i = 0; i < 5; ++i)
			myInts->a[i] = (maven::Object*) new intArray(10);
		((objectArray*) myInts->a[0])->a[0];
	}
	
	maven_boolean initMaven() {
		// push current thread
		// bug #25: to do with pthread_self()
		
		// init random number algorithm
		mt[0] = time(NULL) & 0xffffffffUL;
		
		for(mti = 1; mti < N; mti++) {
			mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
			/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
			/* In the previous versions, MSBs of the seed affect   */
			/* only MSBs of the array mt[].                        */
			/* 2002/01/09 modified by Makoto Matsumoto             */
			mt[mti] &= 0xffffffffUL;
			/* for >32 bit machines */
		}
		
		// now for the data type min/max
		float* float_val = new float;
		*((int*) float_val) = 0x7f800000;
		maven::Float$static::POSITIVE_INFINITY = *float_val;
		*((int*) float_val) = 0xff800000;
		maven::Float$static::NEGATIVE_INFINITY = *float_val;
		*((int*) float_val) = 0x7f7fffff;
		maven::Float$static::MAX_VALUE = *float_val;
		*((int*) float_val) = 0x1;
		maven::Float$static::MIN_VALUE = *float_val;
		*((int*) float_val) = 0x7fc00000;
		maven::Float$static::NaN = *float_val;
		
		double* double_val = new double;
		*((long long*) double_val) = 0x7ff0000000000000LL;
		maven::Double$static::POSITIVE_INFINITY = *double_val;
		*((long long*) double_val) = 0xfff0000000000000LL;
		maven::Double$static::NEGATIVE_INFINITY = *double_val;
		*((long long*) double_val) = 0x7fefffffffffffffLL;
		maven::Double$static::MAX_VALUE = *double_val;
		*((long long*) double_val) = 0x1L;
		maven::Double$static::MIN_VALUE = *double_val;
		*((long long*) double_val) = 0x7ff8000000000000LL;
		maven::Double$static::NaN = *double_val;
		
		return true;
	}
	
}
