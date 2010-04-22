#include "Double.h"

namespace maven {
	
	namespace Double$static {
		mdouble MAX_VALUE;
		mdouble MIN_VALUE;
		mdouble POSITIVE_INFINITY;
		mdouble NEGATIVE_INFINITY;
		mdouble NaN;
	}
	
	Double::Double() {
		super("maven.Double");
		value = 0.0f;
	}
	
	Double::Double(mdouble newValue) {
		super("maven.Double");
		value = newValue;
	}
	
	mboolean Double::toBoolean() {
		return (value != 0.0f);
	}
	
	mbyte Double::toByte() {
		return (mbyte) value;
	}
	
	mchar Double::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Double::toData() {
		maven::Data* d = new maven::Data();
		d->writeDouble(value);
		return d;
	}
	
	mdouble Double::toDouble() {
		return value;
	}
	
	mfloat Double::toFloat() {
		return (mfloat) value;
	}
	
	mint Double::toInteger() {
		return (mint) value;
	}
	
	mlong Double::toLong() {
		return (mlong) value;
	}
	
	mquad Double::toQuad() {
		return (mquad) value;
	}
	
	mshort Double::toShort() {
		return (mshort) value;
	}
	
	maven::String* Double::toString() {
		return maven::String::valueOf(value);
	}

}
