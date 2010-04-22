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
	
	maven::String* Long::toString() {
		return maven::String::valueOf(value);
	}

}
