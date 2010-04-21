#ifndef MAVENCORE_MAVEN_THREAD
#define MAVENCORE_MAVEN_THREAD 1

#include "../mavencoreclean.h"
#include "Selector.h"

namespace maven {
	
	class Thread extends maven::Object {
		// internals
#if MAVEN_OS == 1
		public_variable pthread_attr_t attr;
		public_variable pthread_t thread;
#endif
		public_variable maven::Selector* s;
		
		// visible methods
		public_constructor Thread();
		public_constructor Thread(maven::Selector* s);
		
		public_method maven_int run();
		
		public_static_method maven_int detach(maven::Selector* s);
		public_static_method maven_int detach(maven::Selector* s, maven::objectArray* argv);
		public_static_method void waitAll();
		public_static_method maven_int activeThreads();
	};
	
}

#endif
