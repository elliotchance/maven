#include "maven.Selector.h"
#include "maven.Object.h"

namespace maven {
	
#if MAVEN_OS == 1
	Selector::Selector(void* (*selector)(void*)) {
#elif MAVEN_OS == 2
	Selector::Selector(maven_int (*selector)(void*)) {
#endif
		super("maven.Selector");
		ptr = selector;
	}
	
	void* Selector::call(void* argv) {
#if MAVEN_OS == 1
		return ptr(argv);
#elif MAVEN_OS == 2
		return voidiseLong(ptr(argv));
#endif
	}
	
	void* Selector::voidiseQuad(maven_quad x) {
		maven_quad* r = new maven_quad[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseBoolean(maven_boolean x) {
		maven_boolean* r = new maven_boolean[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseByte(maven_byte x) {
		maven_byte* r = new maven_byte[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseChar(maven_char x) {
		maven_char* r = new maven_char[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseFloat(maven_float x) {
		maven_float* r = new maven_float[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseDouble(maven_double x) {
		maven_double* r = new maven_double[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseInt(maven_int x) {
		maven_int* r = new maven_int[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseLong(maven_long x) {
		maven_long* r = new maven_long[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseShort(maven_short x) {
		maven_short* r = new maven_short[1];
		*r = x;
		return r;
	}
	
}
