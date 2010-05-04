#ifndef MAVENCORE_MAVEN_SYSTEM
#define MAVENCORE_MAVEN_SYSTEM 1

#include <iostream>

#include "../mavencore.h"
#include "String.h"

#define MAVEN_SYSTEM_PREC_32  7
#define MAVEN_SYSTEM_PREC_64  14
#define MAVEN_SYSTEM_PREC_128 14

namespace maven {
	
	class String;
	class objectArray;
	
	namespace System$static {
		extern int DEFAULT_PRECISION;
		extern int minPrecision;
		extern int maxPrecision;
	}
	
	class System {
		// these are internal and hidden from maven
		public_constructor System();
		
		public_method std::string renderFloatToString(mquad o, int maxPrec);
		public_method std::string renderBooleanToString(mboolean b);
		
		// visible methods
		public_method mvoid printf(maven::String* format, maven::objectArray* args);
		public_method mvoid print(mboolean a);
		public_method mvoid print(mbyte a);
		public_method mvoid print(mchar a);
		public_method mvoid print(mdouble a);
		public_method mvoid print(mfloat a);
		public_method mvoid print(mint a);
		public_method mvoid print(mlong a);
		public_method mvoid print(mshort a);
		public_method mvoid print(mquad a);
		public_method mvoid print(maven::String* a);
		public_method mvoid println(mboolean a);
		public_method mvoid println(mbyte a);
		public_method mvoid println(mchar a);
		public_method mvoid println(mdouble a);
		public_method mvoid println(mfloat a);
		public_method mvoid println(mint a);
		public_method mvoid println(mlong a);
		public_method mvoid println(mshort a);
		public_method mvoid println(mquad a);
		public_method mvoid println(maven::String* a);
		public_method mvoid println();
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
		public_method mvoid die(maven::String* a);
	};

}

#endif
