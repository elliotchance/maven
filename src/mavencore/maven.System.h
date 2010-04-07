#ifndef MAVENCORE_MAVEN_SYSTEM
#define MAVENCORE_MAVEN_SYSTEM 1

#include "mavencore.h"
#include "maven.String.h"

namespace maven {
	
	class String;
	
	class System {
		// these are internal and hidden from maven
		public_constructor System();
		
		// visible methods
		public_method void print(maven_boolean a);
		public_method void print(maven_byte a);
		public_method void print(maven_char a);
		public_method void print(maven_double a);
		public_method void print(maven_float a);
		public_method void print(maven_int a);
		public_method void print(maven_long a);
		public_method void print(maven_short a);
		public_method void print(maven_quad a);
		public_method void print(maven::String* a);
		public_method void println(maven_boolean a);
		public_method void println(maven_byte a);
		public_method void println(maven_char a);
		public_method void println(maven_double a);
		public_method void println(maven_float a);
		public_method void println(maven_int a);
		public_method void println(maven_long a);
		public_method void println(maven_short a);
		public_method void println(maven_quad a);
		public_method void println(maven::String* a);
		public_method void println();
		public_method maven::String* getString();
		public_method maven_boolean getBoolean();
		public_method maven_byte getByte();
		public_method maven_char getChar();
		public_method maven_double getDouble();
		public_method maven_float getFloat();
		public_method maven_int getInt();
		public_method maven_long getLong();
		public_method maven_quad getQuad();
		public_method maven_short getShort();
		public_method void die(maven::String* a);
	};

}

#endif
