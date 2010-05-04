#ifndef MAVENCORE_MAVEN_STRING
#define MAVENCORE_MAVEN_STRING 1

#include "../mavencore.h"
#include "ObjectBase.h"

namespace maven {
	
	class Data;
	
	class String : public ObjectBase {
		
		// we cannot directly inherit from maven.Object because otherwise each class would require
		// each other, so we move the important stuff into the String class manually
		/*public_variable maven::String* className;
		public_variable constant mint retain;*/
		
		// type conversion
		public_method mboolean toBoolean();
		public_method mbyte toByte();
		public_method mchar toCharacter();
		public_method maven::Data* toData();
		public_method mdouble toDouble();
		public_method mfloat toFloat();
		public_method mint toInteger();
		public_method mlong toLong();
		public_method mquad toQuad();
		public_method mshort toShort();
		public_method maven::String* toString();
		
		// these are internal and hidden from maven
		public_variable mbyte* s;
		public_variable mint len;
		public_variable String(const mbyte* newString);
		
		// constrctors
		public_constructor String();
		
		// manipulation
		public_method maven::String* append(maven::String* str);
		public_method void erase();
		public_method maven::String* substring(mint length);
		public_method maven::String* substring(mint start, mint length);
		
		// searching
		public_method mint indexOf(maven::String* otherString);
		public_method mchar charAt(int index);
		
		// testing
		public_method mint compare(maven::String* otherString);
		public_method mboolean isEmpty();
		public_method mint length();
		
		public_static_method maven::String* valueOf(mboolean value);
		public_static_method maven::String* valueOf(mbyte value);
		public_static_method maven::String* valueOf(mchar value);
		public_static_method maven::String* valueOf(mdouble value);
		public_static_method maven::String* valueOf(mfloat value);
		public_static_method maven::String* valueOf(mint value);
		public_static_method maven::String* valueOf(mlong value);
		public_static_method maven::String* valueOf(mquad value);
		public_static_method maven::String* valueOf(mshort value);
		
		// misc
		public_method mint levenshtein(maven::String* otherString);
		
		// hashes
		public_method maven::String* md5();
		public_method maven::String* sha1();
		
		// operators
		public_method maven::String* operator_plus(maven::String* str2);
		public_method maven::String* operator_plus(mquad str2);
		public_method mboolean operator_equal(maven::String* str2);
		public_method maven::String* operator_assignplus(maven::String* str2);
	};
	
}

#endif
