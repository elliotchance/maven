/**
 
 The point of the mavencoreclean.h file is to wipe the maven types
 to make it more compatible with original C++ code.
 
 It is recommended you include this header file into your project
 instead of the mavencore.h header file and use the maven_int,
 maven_boolean etc types.
 
 */

#ifndef MAVENCORECLEAN_H
#define MAVENCORECLEAN_H 1

#include "mavencore.h"

// undefine the masking data types
#undef boolean
#undef byte
#undef char
#undef long
#undef quad

#endif
