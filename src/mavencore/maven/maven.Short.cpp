#include "maven.Short.h"

namespace maven {
	
	Short::Short() {
		super("maven.Short");
		value = 0;
	}
	
	Short::Short(maven_short newValue) {
		super("maven.Short");
		value = newValue;
	}
	
	maven::String* Short::toString() {
		return maven::String::valueOf(value);
	}

}
