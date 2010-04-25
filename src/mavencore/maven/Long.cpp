#include "Long.h"

namespace maven {
	
	Long::Long() {
		super("maven.Long");
		value = 0;
	}
	
	Long::Long(mlong newValue) {
		super("maven.Long");
		value = newValue;
	}
	
	mboolean Long::toBoolean() {
		return (value != 0.0f);
	}
	
	mbyte Long::toByte() {
		return (mbyte) value;
	}
	
	mchar Long::toCharacter() {
		return (mchar) value;
	}
	
	maven::Data* Long::toData() {
		maven::Data* d = new maven::Data();
		d->writeLong(value);
		return d;
	}
	
	mdouble Long::toDouble() {
		return (mdouble) value;
	}
	
	mfloat Long::toFloat() {
		return (mfloat) value;
	}
	
	mint Long::toInteger() {
		return (mint) value;
	}
	
	mlong Long::toLong() {
		return (mlong) value;
	}
	
	mquad Long::toQuad() {
		return value;
	}
	
	mshort Long::toShort() {
		return (mshort) value;
	}
	
	maven::String* Long::toString() {
		return maven::String::valueOf(value);
	}

}
