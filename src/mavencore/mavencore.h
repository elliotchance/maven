/*
 *  mavencore.h
 *  maven
 *
 *  Created by Elliot Chance on 15/05/09.
 *  Copyright 2009 Chance MEDIA Pty Ltd. All rights reserved.
 *
 */

#ifndef MAVENCORE_H
#define MAVENCORE_H 1

#include "../maven/config.h"

#include <vector>

#if MAVEN_OS == 1
#include <pthread.h>
#elif MAVEN_OS == 2
#include <windows.h>
#endif

// maven types
typedef bool           mboolean;
typedef char           mbyte;
typedef unsigned short mchar;
typedef double         mdouble;
typedef float          mfloat;
typedef int            mint;
typedef long long      mlong;
typedef long double    mquad;
typedef short          mshort;
typedef void           mvoid;

// for mavencore
#define public_method           public: virtual 
#define public_static_method    public: static 
#define public_variable         public: 
#define public_static_variable  public: static
#define public_constructor      public: 
#define private_method          private: virtual 
#define private_static_method   private: static 
#define private_variable        private: 
#define private_static_variable private: static
#define private_constructor     private: 

// for catching potential memory problems
#define catchMalloc(__variable, __objName) \
	if(__variable == 0) { \
		printf("ERROR: malloc() failed for %s\n", __objName); \
	}
#define catchNilObjectException(__variable, __action) \
	if(__variable == 0) { \
		__action; \
	}
#define newStatic(objectName, variableName) namespace objectName##$static { variableName; }
#define externStatic(objectName, variableName) namespace objectName##$static { extern variableName; }
#define getStatic(objectName, variableName) objectName##$static::variableName

// other keywords
#define mnil 0
#define extends : public
#define readonly

// random number generation for Math.random()
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   // constant vector a
#define UPPER_MASK 0x80000000UL // most significant w-r bits
#define LOWER_MASK 0x7fffffffUL // least significant r bits
extern mlong mt[N];        // the array for the state vector
extern mint mti;           // mti==N+1 means mt[N] is not initialized

#if MAVEN_OS == 1
static std::vector<pthread_t> threads;
#elif MAVEN_OS == 2
static std::vector<HANDLE> threads;
#endif

// operator overloading
#define operator_assign             operator_3D     /* =   */
#define operator_plus               operator_2B     /* +   */
#define operator_minus              operator_2D     /* -   */
#define operator_multply            operator_2A     /* *   */
#define operator_divide             operator_2F     /* /   */
#define operator_modulo             operator_25     /* %   */
#define operator_autoinc            operator_2B2B   /* ++  */
#define operator_autodec            operator_2D2D   /* --  */

#define operator_assignplus         operator_2B3D   /* +=  */
#define operator_assignminus        operator_2D3D   /* -=  */
#define operator_assignmultply      operator_2A3D   /* *=  */
#define operator_assigndivide       operator_2F3D   /* /=  */
#define operator_assignmodulo       operator_253D   /* %=  */

#define operator_lessthan           operator_3C     /* <   */
#define operator_lessthanequal      operator_3C3D   /* <=  */
#define operator_greaterthan        operator_3E     /* >   */
#define operator_greaterthanequal   operator_3E3D   /* >=  */
#define operator_equal              operator_3D3D   /* ==  */
#define operator_notequal           operator_213D   /* !=  */

#define operator_not                operator_21     /* !   */
#define operator_and                operator_2626   /* &&  */
#define operator_or                 operator_7C7C   /* ||  */

#define operator_bitwiseleft        operator_3C3C   /* <<  */
#define operator_assignbitwiseleft  operator_3C3C3D /* <<= */
#define operator_bitwiseright       operator_3E3E   /* >>  */
#define operator_assignbitwiseright operator_3E3E3D /* >>= */ 
#define operator_bitwisenot         operator_7E     /* ~   */
#define operator_bitwiseand         operator_26     /* &   */
#define operator_bitwiseor          operator_7C     /* |   */
#define operator_assignbitwiseand   operator_263D   /* &=  */
#define operator_assignbitwiseor    operator_7C3D   /* |=  */
#define operator_bitwisexor         operator_5E     /* ^   */
#define operator_assignbitwisexor   operator_5E3D   /* ^=  */

// these headers must be automatically included
#include "maven/Array.h"
#include "maven/Object.h"
#include "maven/String.h"
#include "maven/System.h"
#include "maven/Selector.h"

namespace maven {
	
	mboolean initMaven();
	
	namespace Boolean$static {
		extern mboolean MAX_VALUE;
		extern mboolean MIN_VALUE;
	}
	
	namespace Byte$static {
		extern mbyte MAX_VALUE;
		extern mbyte MIN_VALUE;
	}
	
	namespace Float$static {
		extern mfloat MAX_VALUE;
		extern mfloat MIN_VALUE;
		extern mfloat POSITIVE_INFINITY;
		extern mfloat NEGATIVE_INFINITY;
		extern mfloat NaN;
	}
	
	namespace Double$static {
		extern mdouble MAX_VALUE;
		extern mdouble MIN_VALUE;
		extern mdouble POSITIVE_INFINITY;
		extern mdouble NEGATIVE_INFINITY;
		extern mdouble NaN;
	}
	
}

#endif
