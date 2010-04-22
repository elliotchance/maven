#include "BoundsException.h"

namespace maven {
	
	BoundsException::BoundsException() {
		super("maven.BoundsException");
	}
	
	BoundsException::BoundsException(maven::String* variable, maven::String* filename, mint occuredLine) {
		super("maven.BoundsException");
		line = occuredLine;
		file = filename;
		reason = variable;
	}
	
}
