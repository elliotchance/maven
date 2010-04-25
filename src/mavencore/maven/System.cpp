#include "System.h"

namespace maven {
	
	System::System() {
		// console defaults
		std::cout.precision(6);
	}
	
	void System::print(mboolean o) {
		std::cout << o;
	}
	
	void System::print(mbyte o) {
		// bytes are printed as ints
		std::cout << (int) o;
	}
	
	void System::print(mchar o) {
		printf("%c", o);
	}
	
	void System::print(mdouble o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_64);
		std::cout << o;
	}
	
	void System::print(mfloat o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_32);
		std::cout << o;
	}

	void System::print(mint o) {
		std::cout << o;
	}
	
	void System::print(mquad o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_128);
		std::cout << o;
	}
	
	void System::print(mlong o) {
		std::cout << o;
	}
	
	void System::print(mshort o) {
		std::cout << o;
	}
	
	void System::print(maven::String* o) {
		if(o == NULL)
			return;
		std::cout << o->s;
	}
	
	void System::println(mboolean o) {
		std::cout << o << std::endl;
	}
	
	void System::println(mbyte o) {
		// bytes are printed as ints
		std::cout << (int) o << std::endl;
	}
	
	void System::println(mchar o) {
		printf("%c\n", o);
	}
	
	void System::println(mdouble o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_64);
		std::cout << o << std::endl;
	}
	
	void System::println(mfloat o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_32);
		std::cout << o << std::endl;
	}
	
	void System::println(mint o) {
		std::cout << o << std::endl;
	}
	
	void System::println(mquad o) {
		std::cout.precision(MAVEN_SYSTEM_PREC_128);
		std::cout << o << std::endl;
	}
	
	void System::println(mlong o) {
		std::cout << o << std::endl;
	}
	
	void System::println(mshort o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven::String* o) {
		if(o == NULL)
			return;
		std::cout << o->s << std::endl;
	}
	
	void System::die(maven::String* o) {
		if(o != NULL)
			std::cout << o->s << std::endl;
		exit(1);
	}
	
	void System::println() {
		std::cout << std::endl;
	}
	
	maven::String* System::getString() {
		mbyte buf[256];
		std::cin.getline(buf, 255);
		return new maven::String((mbyte*) buf);
	}
	
	mint System::getInt() {
		mint in;
		std::cin >> in;
		return in;
	}
	
	mboolean System::getBoolean() {
		mint in;
		std::cin >> in;
		return (in != 0);
	}
	
	mbyte System::getByte() {
		mbyte in;
		std::cin >> in;
		return in;
	}
	
	mchar System::getChar() {
		char in;
		std::cin >> in;
		return (mchar) in;
	}
	
	mdouble System::getDouble() {
		mdouble in;
		std::cin >> in;
		return in;
	}
	
	mfloat System::getFloat() {
		mfloat in;
		std::cin >> in;
		return in;
	}
	
	mlong System::getLong() {
		mlong in;
		std::cin >> in;
		return in;
	}
	
	mquad System::getQuad() {
		mfloat in;
		std::cin >> in;
		return in;
	}
	
	mshort System::getShort() {
		mshort in;
		std::cin >> in;
		return in;
	}

}
