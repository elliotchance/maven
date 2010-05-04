#include "System.h"

#include <cmath>

namespace maven {
	
	namespace System$static {
		int DEFAULT_PRECISION = MAVEN_SYSTEM_PREC_128;
		int minPrecision = 0;
		int maxPrecision = MAVEN_SYSTEM_PREC_128;
	}
	
	std::string System::renderFloatToString(mquad o, int maxPrec) {
		std::string out = "";
		int temp, d = maxPrec - floor(std::log(o) / std::log(10));
		double size = pow(10.0, floor(std::log(o) / std::log(10)));
		
		// render
		for(; size > std::pow(10.0, (double) -std::min(d, maven::System$static::maxPrecision + 1)); size /= 10.0) {
			if(size == 0.1)
				out += ".";
			temp = o / size;
			out += (char) '0' + temp;
			o -= (temp * size);
		}
		
		// truncate
		int dot = out.find('.');
		for(int i = out.length() - 1; i > dot + maven::System$static::minPrecision; --i) {
			if(out.at(i) != '0')
				break;
			out = out.substr(0, i);
		}
		
		// expand
		int pad;
		if(dot == std::string::npos) {
			pad = maven::System$static::minPrecision - 1;
			if(pad >= 0)
				out += ".";
		} else
			pad = maven::System$static::minPrecision - (out.length() - dot);
		
		for(int i = 0; i <= pad; ++i)
			out += "0";
		
		return out;
	}
	
	std::string System::renderBooleanToString(mboolean b) {
		if(b)
			return "true";
		return "false";
	}
	
	System::System() {
	}
	
	void System::print(mboolean o) {
		std::cout << renderBooleanToString(o);
	}
	
	void System::print(mbyte o) {
		// bytes are printed as ints
		std::cout << (int) o;
	}
	
	void System::print(mchar o) {
		std::printf("%c", o);
	}
	
	void System::print(mdouble o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_64);
	}
	
	void System::print(mfloat o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_32);
	}

	void System::print(mint o) {
		std::cout << o;
	}
	
	void System::print(mquad o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_128);
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
		std::cout << renderBooleanToString(o) << std::endl;
	}
	
	void System::println(mbyte o) {
		// bytes are printed as ints
		std::cout << (int) o << std::endl;
	}
	
	void System::println(mchar o) {
		std::printf("%c\n", o);
	}
	
	void System::println(mdouble o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_64) << std::endl;
	}
	
	void System::println(mfloat o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_32) << std::endl;
	}
	
	void System::println(mint o) {
		std::cout << o << std::endl;
	}
	
	void System::println(mquad o) {
		std::cout << renderFloatToString(o, MAVEN_SYSTEM_PREC_128) << std::endl;
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
