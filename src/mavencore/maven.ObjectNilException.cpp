#include "maven.ObjectNilException.h"

namespace maven {
	
	ObjectNilException::ObjectNilException() {
		super("maven.ObjectNilException");
	}
	
	ObjectNilException::ObjectNilException(maven::String* variable, maven::String* filename, maven_int occuredLine) {
		super("maven.ObjectNilException");
		line = occuredLine;
		file = filename;
		reason = variable;
	}
	
}
