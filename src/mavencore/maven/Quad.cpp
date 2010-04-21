#include "Quad.h"

namespace maven {
	
	Quad::Quad() {
		super("maven.Quad");
		value = 0;
	}
	
	Quad::Quad(maven_quad newValue) {
		super("maven.Quad");
		value = newValue;
	}
	
	maven_boolean Quad::toBoolean() {
		return (value != 0.0f);
	}
	
	maven_byte Quad::toByte() {
		return (maven_byte) value;
	}
	
	maven_char Quad::toCharacter() {
		return (maven_char) value;
	}
	
	maven::Data* Quad::toData() {
		maven::Data* d = new maven::Data();
		d->writeQuad(value);
		return d;
	}
	
	maven_double Quad::toDouble() {
		return (maven_double) value;
	}
	
	maven_float Quad::toFloat() {
		return (maven_float) value;
	}
	
	maven_int Quad::toInteger() {
		return (maven_int) value;
	}
	
	maven_long Quad::toLong() {
		return (maven_long) value;
	}
	
	maven_quad Quad::toQuad() {
		return value;
	}
	
	maven_short Quad::toShort() {
		return (maven_short) value;
	}
	
	maven::String* Quad::toString() {
		return maven::String::valueOf(value);
	}

}
