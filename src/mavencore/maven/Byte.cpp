#include "Byte.h"

namespace maven {
	
	namespace Byte$static {
		maven_byte MAX_VALUE =  127;
		maven_byte MIN_VALUE = -128;
	}
	
	Byte::Byte() {
		super("maven.Byte");
		value = 0;
	}
	
	Byte::Byte(maven_byte newValue) {
		super("maven.Byte");
		value = newValue;
	}
	
	maven_boolean Byte::toBoolean() {
		return (value != 0);
	}
	
	maven_byte Byte::toByte() {
		return (maven_byte) value;
	}
	
	maven_char Byte::toCharacter() {
		return (maven_char) value;
	}
	
	maven::Data* Byte::toData() {
		maven::Data* d = new maven::Data();
		d->writeByte(value);
		return d;
	}
	
	maven_double Byte::toDouble() {
		return (maven_double) value;
	}
	
	maven_float Byte::toFloat() {
		return (maven_float) value;
	}
	
	maven_int Byte::toInteger() {
		return value;
	}
	
	maven_long Byte::toLong() {
		return (maven_long) value;
	}
	
	maven_quad Byte::toQuad() {
		return (maven_quad) value;
	}
	
	maven_short Byte::toShort() {
		return (maven_short) value;
	}
	
	maven::String* Byte::toString() {
		return maven::String::valueOf(value);
	}

}
