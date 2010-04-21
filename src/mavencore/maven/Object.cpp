#include "Object.h"
#include "String.h"

namespace maven {
	
	Object::Object() {
		super("maven.Object");
	}
	
	Object* Object::super(const maven_byte* childClass) {
		className = new maven::String(childClass);
		return this;
	}
	
	maven_boolean Object::toBoolean() {
		return false;
	}
	
	maven_byte Object::toByte() {
		return 0;
	}
	
	maven_char Object::toCharacter() {
		return 0;
	}
	
	maven::Data* Object::toData() {
		return 0;
	}
	
	maven_double Object::toDouble() {
		return 0;
	}
	
	maven_float Object::toFloat() {
		return 0;
	}
	
	maven_int Object::toInteger() {
		return 0;
	}
	
	maven_long Object::toLong() {
		return 0;
	}
	
	maven_quad Object::toQuad() {
		return 0;
	}
	
	maven_short Object::toShort() {
		return 0;
	}
	
	maven::String* Object::toString() {
		return new maven::String("<Undescriptive Object>");
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
	
	maven_boolean Object::operator_equal(maven::Object* toCompare) {
		return (void*) this == (void*) toCompare;
	}
	
}
