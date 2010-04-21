#include "maven.Thread.h"
#include "maven.Selector.h"

namespace maven {
	
	Thread::Thread() {
		super("maven.Thread");
	}
	
	Thread::Thread(maven::Selector* p) {
		super("maven.Thread");
		s = p;
	}
	
	maven_int Thread::run() {
		// this method assumes no arguments to the detached function
		void** argv = new void*[1];
		argv[0] = maven::Selector::voidiseInt(0);
		
#if MAVEN_OS == 1
		pthread_t thread;
		maven_int r = pthread_create(&thread, NULL, s->ptr, argv);
		threads.push_back(thread);
		return r;
#elif MAVEN_OS == 2
		HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) s->ptr, argv, 0, 0);
		threads.push_back(thread);
		return 0;
#endif
		return 0;
	}
	
	maven_int Thread::detach(maven::Selector* s) {
		// this method assumes no arguments to the detached function
		void* argv = (void*) new maven::objectArray(0);
		
#if MAVEN_OS == 1
		pthread_t thread;
		maven_int r = pthread_create(&thread, NULL, s->ptr, argv);
		threads.push_back(thread);
		return r;
#elif MAVEN_OS == 2
		HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) s->ptr, argv, 0, 0);
		threads.push_back(thread);
		return 0;
#endif
		return 0;
	}
	
	maven_int Thread::detach(maven::Selector* s, maven::objectArray* argv) {
#if MAVEN_OS == 1
		pthread_t thread;
		maven_int r = pthread_create(&thread, NULL, s->ptr, argv);
		threads.push_back(thread);
		return r;
#elif MAVEN_OS == 2
		HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) s->ptr, argv, 0, 0);
		threads.push_back(thread);
		return 0;
#endif
		return 0;
	}
	
	void Thread::waitAll() {
#if MAVEN_OS == 1
		while(threads.size()) {
			pthread_join(threads[0], NULL);
			threads.erase(threads.begin());
		}
#elif MAVEN_OS == 2
		while(threads.size()) {
			WaitForSingleObject(threads[0], INFINITE);
			threads.erase(threads.begin());
		}
#endif
	}
	
	maven_int Thread::activeThreads() {
		return threads.size();
		return 0;
	}
	
}
