#include "Short.h"

namespace maven {
	
	Short::Short() {
		super("maven.Short");
		value = 0;
	}
	
	Short::Short(mshort newValue) {
		super("maven.Short");
		value = newValue;
	}
	
	maven::String* Short::toString() {
		return maven::String::valueOf(value);
	}

}
