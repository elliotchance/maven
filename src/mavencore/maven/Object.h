#ifndef MAVENCORE_MAVEN_OBJECT
#define MAVENCORE_MAVEN_OBJECT 1

#include "../mavencore.h"

namespace maven {
	
	class String;
	class Data;
	class objectArray;
	
	class Object {
		public_variable maven::String* className;
		public_variable constant mint retain;
		
		public_constructor Object();
		public_method void free();
		public_method Object* copy();
		public_method Object* callMethodByName(maven::String* method, maven::objectArray* varargs);
		
		public_method mboolean toBoolean();
		public_method mbyte toByte();
		public_method mchar toCharacter();
		public_method maven::Data* toData();
		public_method mdouble toDouble();
		public_method mfloat toFloat();
		public_method mint toInteger();
		public_method mlong toLong();
		public_method mquad toQuad();
		public_method mshort toShort();
		public_method maven::String* toString();
		
		// internal methods
		maven::Object* super(const mbyte* childClass);
	};
	
	class Array extends maven::Object {
		public_variable constant mlong length;
		public_constructor Array();
	};
	
	class booleanArray extends maven::Array {
		public_variable mboolean* a;
		public_constructor booleanArray(mlong size);
		public_constructor booleanArray(mlong size, mboolean defaultValue);
	};
	
	class byteArray extends maven::Array {
		public_variable mbyte* a;
		public_constructor byteArray(mlong size);
		public_constructor byteArray(mlong size, mbyte defaultValue);
	};
	
	class charArray extends maven::Array {
		public_variable mchar* a;
		public_constructor charArray(mlong size);
		public_constructor charArray(mlong size, mchar defaultValue);
	};
	
	class doubleArray extends maven::Array {
		public_variable mdouble* a;
		public_constructor doubleArray(mlong size);
		public_constructor doubleArray(mlong size, mdouble defaultValue);
	};
	
	class floatArray extends maven::Array {
		public_variable mfloat* a;
		public_constructor floatArray(mlong size);
		public_constructor floatArray(mlong size, mfloat defaultValue);
	};
	
	class longArray extends maven::Array {
		public_variable mlong* a;
		public_constructor longArray(mlong size);
		public_constructor longArray(mlong size, mlong defaultValue);
	};
	
	class shortArray extends maven::Array {
		public_variable mshort* a;
		public_constructor shortArray(mlong size);
		public_constructor shortArray(mlong size, mshort defaultValue);
	};
	
	class intArray extends maven::Array {
		public_variable mint* a;
		public_constructor intArray(mlong size);
		public_constructor intArray(mlong size, mint defaultValue);
		public_constructor intArray(mlong size, mint* values);
	};
	
	class quadArray extends maven::Array {
		public_variable mquad* a;
		public_constructor quadArray(mlong size);
		public_constructor quadArray(mlong size, mquad defaultValue);
	};
	
	class objectArray extends maven::Array {
		public_variable maven::Object** a;
		public_constructor objectArray(mlong size);
		public_constructor objectArray(mlong size, maven::Object** assign);
	};
	
	class Selector extends maven::Object {
#if MAVEN_OS == 1
		public_variable void* (*ptr)(void*);
#elif MAVEN_OS == 2
		public_variable mint (*ptr)(void*);
#endif
		
#if MAVEN_OS == 1
		public_constructor Selector(void* (*selector)(void*));
#elif MAVEN_OS == 2
		public_constructor Selector(mint (*selector)(void*));
#endif
		
		public_method void* call(void* argv);
		
		public_static_method void* voidiseQuad(mquad x);
		public_static_method void* voidiseBoolean(mboolean x);
		public_static_method void* voidiseByte(mbyte x);
		public_static_method void* voidiseChar(mchar x);
		public_static_method void* voidiseFloat(mfloat x);
		public_static_method void* voidiseDouble(mdouble x);
		public_static_method void* voidiseInt(mint x);
		public_static_method void* voidiseLong(mlong x);
		public_static_method void* voidiseShort(mshort x);
	};
	
}

#endif
