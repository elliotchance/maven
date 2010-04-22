#ifndef MAVENCORE_MAVEN_THREAD
#define MAVENCORE_MAVEN_THREAD 1

#include "../mavencore.h"
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
		
		public_method mint run();
		
		public_static_method mint detach(maven::Selector* s);
		public_static_method mint detach(maven::Selector* s, maven::objectArray* argv);
		public_static_method void waitAll();
		public_static_method mint activeThreads();
	};
	
}

#endif
