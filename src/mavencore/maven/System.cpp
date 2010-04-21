#include "System.h"

namespace maven {
	
	System::System() {
		// console defaults
		std::cout.precision(6);
	}
	
	void System::print(maven_boolean o) {
		std::cout << o;
	}
	
	void System::print(maven_byte o) {
		std::cout << "a" << std::endl;
		// bytes are printed as ints
		std::cout << (int) o;
	}
	
	void System::print(maven_char o) {
		printf("%c", o);
	}
	
	void System::print(maven_double o) {
		std::cout << "c" << std::endl;
		std::cout << o;
	}
	
	void System::print(maven_float o) {
		std::cout << "d" << std::endl;
		std::cout << o;
	}

	void System::print(maven_int o) {
		std::cout << "e" << std::endl;
		std::cout << o;
	}
	
	void System::print(maven_quad o) {
		std::cout << "f" << std::endl;
		std::cout << o;
	}
	
	void System::print(maven_long o) {
		std::cout << "g" << std::endl;
		std::cout << o;
	}
	
	void System::print(maven_short o) {
		std::cout << "h" << std::endl;
		std::cout << o;
	}
	
	void System::print(maven::String* o) {
		if(o == NULL) return;
		std::cout << o->s;
	}
	
	void System::println(maven_boolean o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_byte o) {
		// bytes are printed as ints
		std::cout << (int) o << std::endl;
	}
	
	void System::println(maven_char o) {
		printf("%c\n", o);
	}
	
	void System::println(maven_double o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_float o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_int o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_quad o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_long o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven_short o) {
		std::cout << o << std::endl;
	}
	
	void System::println(maven::String* o) {
		if(o == NULL) return;
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
		maven_byte buf[256];
		std::cin.getline(buf, 255);
		return new maven::String((maven_byte*) buf);
	}
	
	maven_int System::getInt() {
		maven_int in;
		std::cin >> in;
		return in;
	}
	
	maven_boolean System::getBoolean() {
		maven_int in;
		std::cin >> in;
		return (in != 0);
	}
	
	maven_byte System::getByte() {
		maven_byte in;
		std::cin >> in;
		return in;
	}
	
	maven_char System::getChar() {
		c_char in;
		std::cin >> in;
		return (maven_char) in;
	}
	
	maven_double System::getDouble() {
		maven_double in;
		std::cin >> in;
		return in;
	}
	
	maven_float System::getFloat() {
		maven_float in;
		std::cin >> in;
		return in;
	}
	
	maven_long System::getLong() {
		maven_long in;
		std::cin >> in;
		return in;
	}
	
	maven_quad System::getQuad() {
		maven_float in;
		std::cin >> in;
		return in;
	}
	
	maven_short System::getShort() {
		maven_short in;
		std::cin >> in;
		return in;
	}

}
