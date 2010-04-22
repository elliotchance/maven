#include "Quad.h"

namespace maven {
	
	Quad::Quad() {
		super("maven.Quad");
		value = 0;
	}
	
	Quad::Quad(mquad newValue) {
		super("maven.Quad");
		value = newValue;
	}
	
	mboolean Quad::toBoolean() {
		return (value != 0.0f);
	}
	
	mbyte Quad::toByte() {
		return (mbyte) value;
	}
	
	mchar Quad::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Quad::toData() {
		maven::Data* d = new maven::Data();
		d->writeQuad(value);
		return d;
	}
	
	mdouble Quad::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Quad::toFloat() {
		return (mfloat) value;
	}
	
	mint Quad::toInteger() {
		return (mint) value;
	}
	
	mlong Quad::toLong() {
		return (mlong) value;
	}
	
	mquad Quad::toQuad() {
		return value;
	}
	
	mshort Quad::toShort() {
		return (mshort) value;
	}
	
	maven::String* Quad::toString() {
		return maven::String::valueOf(value);
	}

}
