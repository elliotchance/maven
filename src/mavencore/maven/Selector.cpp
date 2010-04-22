#include "Selector.h"
#include "Object.h"

namespace maven {
	
#if MAVEN_OS == 1
	Selector::Selector(void* (*selector)(void*)) {
#elif MAVEN_OS == 2
	Selector::Selector(mint (*selector)(void*)) {
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
	
	void* Selector::voidiseQuad(mquad x) {
		mquad* r = new mquad[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseBoolean(mboolean x) {
		mboolean* r = new mboolean[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseByte(mbyte x) {
		mbyte* r = new mbyte[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseChar(mchar x) {
		mchar* r = new mchar[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseFloat(mfloat x) {
		mfloat* r = new mfloat[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseDouble(mdouble x) {
		mdouble* r = new mdouble[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseInt(mint x) {
		mint* r = new mint[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseLong(mlong x) {
		mlong* r = new mlong[1];
		*r = x;
		return r;
	}
	
	void* Selector::voidiseShort(mshort x) {
		mshort* r = new mshort[1];
		*r = x;
		return r;
	}
	
}
