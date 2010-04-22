#ifndef MAVENCORE_MAVEN_SYSTEM
#define MAVENCORE_MAVEN_SYSTEM 1

#include <iostream>

#include "../mavencore.h"
#include "String.h"

namespace maven {
	
	class String;
	
	class System {
		// these are internal and hidden from maven
		public_constructor System();
		
		// visible methods
		public_method void print(mboolean a);
		public_method void print(mbyte a);
		public_method void print(mchar a);
		public_method void print(mdouble a);
		public_method void print(mfloat a);
		public_method void print(mint a);
		public_method void print(mlong a);
		public_method void print(mshort a);
		public_method void print(mquad a);
		public_method void print(maven::String* a);
		public_method void println(mboolean a);
		public_method void println(mbyte a);
		public_method void println(mchar a);
		public_method void println(mdouble a);
		public_method void println(mfloat a);
		public_method void println(mint a);
		public_method void println(mlong a);
		public_method void println(mshort a);
		public_method void println(mquad a);
		public_method void println(maven::String* a);
		public_method void println();
		public_method maven::String* getString();
		public_method mboolean getBoolean();
		public_method mbyte getByte();
		public_method mchar getChar();
		public_method mdouble getDouble();
		public_method mfloat getFloat();
		public_method mint getInt();
		public_method mlong getLong();
		public_method mquad getQuad();
		public_method mshort getShort();
		public_method void die(maven::String* a);
	};

}

#endif
