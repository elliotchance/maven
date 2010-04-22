#include "Integer.h"

namespace maven {
	
	Integer::Integer() {
		super("maven.Integer");
		value = 0;
	}
	
	Integer::Integer(mint newValue) {
		super("maven.Integer");
		value = newValue;
	}
	
	mboolean Integer::toBoolean() {
		return (value != 0);
	}
	
	mbyte Integer::toByte() {
		return (mbyte) value;
	}
	
	mchar Integer::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Integer::toData() {
		maven::Data* d = new maven::Data();
		d->writeInt(value);
		return d;
	}
	
	mdouble Integer::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Integer::toFloat() {
		return (mfloat) value;
	}
	
	mint Integer::toInteger() {
		return value;
	}
	
	mlong Integer::toLong() {
		return (mlong) value;
	}
	
	mquad Integer::toQuad() {
		return (mquad) value;
	}
	
	mshort Integer::toShort() {
		return (mshort) value;
	}
	
	maven::String* Integer::toString() {
		return maven::String::valueOf(value);
	}

}
