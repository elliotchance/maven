#include "Boolean.h"

namespace maven {
	
	namespace Boolean$static {
		mboolean MAX_VALUE = true;
		mboolean MIN_VALUE = false;
	}
	
	Boolean::Boolean() {
		super("maven.Boolean");
		value = false;
	}
	
	Boolean::Boolean(mboolean newValue) {
		super("maven.Boolean");
		value = newValue;
	}
	
	mboolean Boolean::toBoolean() {
		return value;
	}
	
	mbyte Boolean::toByte() {
		return (value ? 1 : 0);
	}
	
	mchar Boolean::toCharacter() {
		return (value ? 'T' : 'F');
	}
	
	maven::Data* Boolean::toData() {
		maven::Data* d = new maven::Data();
		d->writeBoolean(value);
		return d;
	}
	
	mdouble Boolean::toDouble() {
		return (value ? 1.0 : 0.0);
	}
	
	mfloat Boolean::toFloat() {
		return (value ? 1.0f : 0.0f);
	}
	
	mint Boolean::toInteger() {
		return (value ? 1 : 0);
	}
	
	mlong Boolean::toLong() {
		return (value ? 1L : 0L);
	}
	
	mquad Boolean::toQuad() {
		return (value ? 1.0 : 0.0);
	}
	
	mshort Boolean::toShort() {
		return (value ? 1 : 0);
	}
	
	maven::String* Boolean::toString() {
		return maven::String::valueOf(value);
	}

}
