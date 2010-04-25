#include "Short.h"

namespace maven {
	
	Short::Short() {
		super("maven.Short");
		value = 0;
	}
	
	Short::Short(mshort newValue) {
		super("maven.Short");
		value = newValue;
	}
	
	mboolean Short::toBoolean() {
		return (value != 0.0f);
	}
	
	mbyte Short::toByte() {
		return (mbyte) value;
	}
	
	mchar Short::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Short::toData() {
		maven::Data* d = new maven::Data();
		d->writeShort(value);
		return d;
	}
	
	mdouble Short::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Short::toFloat() {
		return (mfloat) value;
	}
	
	mint Short::toInteger() {
		return (mint) value;
	}
	
	mlong Short::toLong() {
		return (mlong) value;
	}
	
	mquad Short::toQuad() {
		return value;
	}
	
	mshort Short::toShort() {
		return (mshort) value;
	}
	
	maven::String* Short::toString() {
		return maven::String::valueOf(value);
	}

}
