#include "Byte.h"

namespace maven {
	
	namespace Byte$static {
		mbyte MAX_VALUE =  127;
		mbyte MIN_VALUE = -128;
	}
	
	Byte::Byte() {
		super("maven.Byte");
		value = 0;
	}
	
	Byte::Byte(mbyte newValue) {
		super("maven.Byte");
		value = newValue;
	}
	
	mboolean Byte::toBoolean() {
		return (value != 0);
	}
	
	mbyte Byte::toByte() {
		return (mbyte) value;
	}
	
	mchar Byte::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Byte::toData() {
		maven::Data* d = new maven::Data();
		d->writeByte(value);
		return d;
	}
	
	mdouble Byte::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Byte::toFloat() {
		return (mfloat) value;
	}
	
	mint Byte::toInteger() {
		return value;
	}
	
	mlong Byte::toLong() {
		return (mlong) value;
	}
	
	mquad Byte::toQuad() {
		return (mquad) value;
	}
	
	mshort Byte::toShort() {
		return (mshort) value;
	}
	
	maven::String* Byte::toString() {
		return maven::String::valueOf(value);
	}

}
