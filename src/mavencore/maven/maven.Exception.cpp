#include "maven.Exception.h"
#include "maven.Integer.h"

namespace maven {
	
	Exception::Exception() {
		super("maven.Exception");
	}
	
	maven::String* Exception::description() {
		std::string r = std::string("\nException: ") + className->s + "\n";
		if(file != NULL)
			r += std::string("    Where: ") + file->s + ", line " + maven::String::valueOf(line)->s + "\n";
		if(reason != NULL)
			r += std::string("   Reason: ") + std::string(reason->s);
		r += std::string("\n");
		return new maven::String(r.c_str());
	}
	
}
