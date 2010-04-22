#include "Float.h"

namespace maven {
	
	namespace Float$static {
		mfloat MAX_VALUE;
		mfloat MIN_VALUE;
		mfloat POSITIVE_INFINITY;
		mfloat NEGATIVE_INFINITY;
		mfloat NaN;
	}
	
	Float::Float() {
		super("maven.Float");
		value = 0.0f;
	}
	
	Float::Float(mfloat newValue) {
		super("maven.Float");
		value = newValue;
	}
	
	mboolean Float::toBoolean() {
		return (value != 0.0f);
	}
	
	mbyte Float::toByte() {
		return (mbyte) value;
	}
	
	mchar Float::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Float::toData() {
		maven::Data* d = new maven::Data();
		d->writeFloat(value);
		return d;
	}
	
	mdouble Float::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Float::toFloat() {
		return value;
	}
	
	mint Float::toInteger() {
		return (mint) value;
	}
	
	mlong Float::toLong() {
		return (mlong) value;
	}
	
	mquad Float::toQuad() {
		return (mquad) value;
	}
	
	mshort Float::toShort() {
		return (mshort) value;
	}
	
	maven::String* Float::toString() {
		return maven::String::valueOf(value);
	}

}
