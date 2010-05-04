#ifndef MAVENCORE_MAVEN_OBJECTBASE
#define MAVENCORE_MAVEN_OBJECTBASE 1

namespace maven {
	class String;
	class Data;
}

class ObjectBase {
public:
	maven::String* className;
	int retain;
	
	virtual mboolean toBoolean() = 0;
	virtual mbyte toByte() = 0;
	virtual mchar toCharacter() = 0;
	virtual maven::Data* toData() = 0;
	virtual mdouble toDouble() = 0;
	virtual mfloat toFloat() = 0;
	virtual mint toInteger() = 0;
	virtual mlong toLong() = 0;
	virtual mquad toQuad() = 0;
	virtual mshort toShort() = 0;
	virtual maven::String* toString() = 0;
};

#endif
