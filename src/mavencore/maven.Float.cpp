#include "maven.Float.h"

namespace maven {
	
	namespace Float$static {
		maven_float MAX_VALUE;
		maven_float MIN_VALUE;
		maven_float POSITIVE_INFINITY;
		maven_float NEGATIVE_INFINITY;
		maven_float NaN;
	}
	
	Float::Float() {
		super("maven.Float");
		value = 0.0f;
	}
	
	Float::Float(maven_float newValue) {
		super("maven.Float");
		value = newValue;
	}
	
	maven_boolean Float::toBoolean() {
		return (value != 0.0f);
	}
	
	maven_byte Float::toByte() {
		return (maven_byte) value;
	}
	
	maven_char Float::toCharacter() {
		return (maven_char) value;
	}
	
	maven::Data* Float::toData() {
		maven::Data* d = new maven::Data();
		d->writeFloat(value);
		return d;
	}
	
	maven_double Float::toDouble() {
		return (maven_double) value;
	}
	
	maven_float Float::toFloat() {
		return value;
	}
	
	maven_int Float::toInteger() {
		return (maven_int) value;
	}
	
	maven_long Float::toLong() {
		return (maven_long) value;
	}
	
	maven_quad Float::toQuad() {
		return (maven_quad) value;
	}
	
	maven_short Float::toShort() {
		return (maven_short) value;
	}
	
	maven::String* Float::toString() {
		return maven::String::valueOf(value);
	}

}
