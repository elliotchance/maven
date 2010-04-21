#include "maven.Boolean.h"

namespace maven {
	
	namespace Boolean$static {
		maven_boolean MAX_VALUE = true;
		maven_boolean MIN_VALUE = false;
	}
	
	Boolean::Boolean() {
		super("maven.Boolean");
		value = false;
	}
	
	Boolean::Boolean(maven_boolean newValue) {
		super("maven.Boolean");
		value = newValue;
	}
	
	maven_boolean Boolean::toBoolean() {
		return value;
	}
	
	maven_byte Boolean::toByte() {
		return (value ? 1 : 0);
	}
	
	maven_char Boolean::toCharacter() {
		return (value ? 'T' : 'F');
	}
	
	maven::Data* Boolean::toData() {
		maven::Data* d = new maven::Data();
		d->writeBoolean(value);
		return d;
	}
	
	maven_double Boolean::toDouble() {
		return (value ? 1.0 : 0.0);
	}
	
	maven_float Boolean::toFloat() {
		return (value ? 1.0f : 0.0f);
	}
	
	maven_int Boolean::toInteger() {
		return (value ? 1 : 0);
	}
	
	maven_long Boolean::toLong() {
		return (value ? 1L : 0L);
	}
	
	maven_quad Boolean::toQuad() {
		return (value ? 1.0 : 0.0);
	}
	
	maven_short Boolean::toShort() {
		return (value ? 1 : 0);
	}
	
	maven::String* Boolean::toString() {
		return maven::String::valueOf(value);
	}

}
