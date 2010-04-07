#include "maven.ClassVariable.h"

namespace maven {
	
	ClassVariable::ClassVariable(maven_boolean _isPublic, maven::String* _name, maven::String* _type) {
		super("maven.ClassVariable");
		isPublic = _isPublic;
		name = _name;
		type = _type;
	}
	
}
