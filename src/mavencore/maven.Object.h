#ifndef MAVENCORE_MAVEN_OBJECT
#define MAVENCORE_MAVEN_OBJECT 1

#include "mavencore.h"

namespace maven {
	
	class String;
	class Data;
	class objectArray;
	
	class Object {
		public_variable maven::String* className;
		public_variable readonly maven_int retain;
		
		public_constructor Object();
		public_method void free();
		public_method Object* copy();
		public_method Object* callMethodByName(maven::String* method, maven::objectArray* varargs);
		
		public_method maven_boolean toBoolean();
		public_method maven_byte toByte();
		public_method maven_char toCharacter();
		public_method maven::Data* toData();
		public_method maven_double toDouble();
		public_method maven_float toFloat();
		public_method maven_int toInteger();
		public_method maven_long toLong();
		public_method maven_quad toQuad();
		public_method maven_short toShort();
		public_method maven::String* toString();
		
		public_method maven_boolean operator_equal(Object* toCompare);
		
		// internal methods
		maven::Object* super(const maven_byte* childClass);
	};
	
	class Array extends maven::Object {
		public_variable readonly maven_long length;
		public_constructor Array();
	};
	
	class booleanArray extends maven::Array {
		public_variable maven_boolean* a;
		public_constructor booleanArray(maven_long size);
		public_constructor booleanArray(maven_long size, maven_boolean defaultValue);
	};
	
	class byteArray extends maven::Array {
		public_variable maven_byte* a;
		public_constructor byteArray(maven_long size);
		public_constructor byteArray(maven_long size, maven_byte defaultValue);
	};
	
	class charArray extends maven::Array {
		public_variable maven_char* a;
		public_constructor charArray(maven_long size);
		public_constructor charArray(maven_long size, maven_char defaultValue);
	};
	
	class doubleArray extends maven::Array {
		public_variable maven_double* a;
		public_constructor doubleArray(maven_long size);
		public_constructor doubleArray(maven_long size, maven_double defaultValue);
	};
	
	class floatArray extends maven::Array {
		public_variable maven_float* a;
		public_constructor floatArray(maven_long size);
		public_constructor floatArray(maven_long size, maven_float defaultValue);
	};
	
	class longArray extends maven::Array {
		public_variable maven_long* a;
		public_constructor longArray(maven_long size);
		public_constructor longArray(maven_long size, maven_long defaultValue);
	};
	
	class shortArray extends maven::Array {
		public_variable maven_short* a;
		public_constructor shortArray(maven_long size);
		public_constructor shortArray(maven_long size, maven_short defaultValue);
	};
	
	class intArray extends maven::Array {
		public_variable maven_int* a;
		public_constructor intArray(maven_long size);
		public_constructor intArray(maven_long size, maven_int defaultValue);
		public_constructor intArray(maven_long size, maven_int* values);
	};
	
	class quadArray extends maven::Array {
		public_variable maven_quad* a;
		public_constructor quadArray(maven_long size);
		public_constructor quadArray(maven_long size, maven_quad defaultValue);
	};
	
	class objectArray extends maven::Array {
		public_variable maven::Object** a;
		public_constructor objectArray(maven_long size);
		public_constructor objectArray(maven_long size, maven::Object** assign);
	};
	
	class Selector extends maven::Object {
#if MAVEN_OS == 1
		public_variable void* (*ptr)(void*);
#elif MAVEN_OS == 2
		public_variable maven_int (*ptr)(void*);
#endif
		
#if MAVEN_OS == 1
		public_constructor Selector(void* (*selector)(void*));
#elif MAVEN_OS == 2
		public_constructor Selector(maven_int (*selector)(void*));
#endif
		
		public_method void* call(void* argv);
		
		public_static_method void* voidiseQuad(maven_quad x);
		public_static_method void* voidiseBoolean(maven_boolean x);
		public_static_method void* voidiseByte(maven_byte x);
		public_static_method void* voidiseChar(maven_char x);
		public_static_method void* voidiseFloat(maven_float x);
		public_static_method void* voidiseDouble(maven_double x);
		public_static_method void* voidiseInt(maven_int x);
		public_static_method void* voidiseLong(maven_long x);
		public_static_method void* voidiseShort(maven_short x);
	};
	
}

#endif
