#include "Object.h"
#include "String.h"

namespace maven {
	
	Object::Object() {
		super("maven.Object");
	}
	
	Object* Object::super(const mbyte* childClass) {
		className = new maven::String(childClass);
		return this;
	}
	
	mboolean Object::toBoolean() {
		return false;
	}
	
	mbyte Object::toByte() {
		return 0;
	}
	
	mchar Object::toCharacter() {
		return 0;
	}
	
	maven::Data* Object::toData() {
		return 0;
	}
	
	mdouble Object::toDouble() {
		return 0;
	}
	
	mfloat Object::toFloat() {
		return 0;
	}
	
	mint Object::toInteger() {
		return 0;
	}
	
	mlong Object::toLong() {
		return 0;
	}
	
	mquad Object::toQuad() {
		return 0;
	}
	
	mshort Object::toShort() {
		return 0;
	}
	
	maven::String* Object::toString() {
		return new maven::String("<Object>");
	}
	
	void Object::free() {
		// needs work
	}
	
	Object* Object::copy() {
		// this method MUST be overrided by child classes for now
		// perhaps in the future there will 
		return new maven::Object();
	}
	
	Object* Object::callMethodByName(maven::String* method, maven::objectArray* varargs) {
		return new maven::Object();
	}
	
}
