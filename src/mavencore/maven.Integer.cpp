#include "maven.Integer.h"

namespace maven {
	
	Integer::Integer() {
		super("maven.Integer");
		value = 0;
	}
	
	Integer::Integer(maven_int newValue) {
		super("maven.Integer");
		value = newValue;
	}
	
	maven_boolean Integer::toBoolean() {
		return (value != 0);
	}
	
	maven_byte Integer::toByte() {
		return (maven_byte) value;
	}
	
	maven_char Integer::toCharacter() {
		return (maven_char) value;
	}
	
	maven::Data* Integer::toData() {
		maven::Data* d = new maven::Data();
		d->writeInt(value);
		return d;
	}
	
	maven_double Integer::toDouble() {
		return (maven_double) value;
	}
	
	maven_float Integer::toFloat() {
		return (maven_float) value;
	}
	
	maven_int Integer::toInteger() {
		return value;
	}
	
	maven_long Integer::toLong() {
		return (maven_long) value;
	}
	
	maven_quad Integer::toQuad() {
		return (maven_quad) value;
	}
	
	maven_short Integer::toShort() {
		return (maven_short) value;
	}
	
	maven::String* Integer::toString() {
		return maven::String::valueOf(value);
	}

}
