#include "maven.Double.h"

namespace maven {
	
	namespace Double$static {
		maven_double MAX_VALUE;
		maven_double MIN_VALUE;
		maven_double POSITIVE_INFINITY;
		maven_double NEGATIVE_INFINITY;
		maven_double NaN;
	}
	
	Double::Double() {
		super("maven.Double");
		value = 0.0f;
	}
	
	Double::Double(maven_double newValue) {
		super("maven.Double");
		value = newValue;
	}
	
	maven_boolean Double::toBoolean() {
		return (value != 0.0f);
	}
	
	maven_byte Double::toByte() {
		return (maven_byte) value;
	}
	
	maven_char Double::toCharacter() {
		return (maven_char) value;
	}
	
	maven::Data* Double::toData() {
		maven::Data* d = new maven::Data();
		d->writeDouble(value);
		return d;
	}
	
	maven_double Double::toDouble() {
		return value;
	}
	
	maven_float Double::toFloat() {
		return (maven_float) value;
	}
	
	maven_int Double::toInteger() {
		return (maven_int) value;
	}
	
	maven_long Double::toLong() {
		return (maven_long) value;
	}
	
	maven_quad Double::toQuad() {
		return (maven_quad) value;
	}
	
	maven_short Double::toShort() {
		return (maven_short) value;
	}
	
	maven::String* Double::toString() {
		return maven::String::valueOf(value);
	}

}
