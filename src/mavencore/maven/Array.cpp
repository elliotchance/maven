#include "Array.h"

namespace maven {
	
	Array::Array() {
		super("maven.Array");
	}
	
	booleanArray::booleanArray(mlong size) {
		super("maven.BooleanArray");
		length = size;
		a = new mboolean[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	booleanArray::booleanArray(mlong size, mboolean defaultValue) {
		super("maven.BooleanArray");
		length = size;
		a = new mboolean[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	byteArray::byteArray(mlong size) {
		super("maven.ByteArray");
		length = size;
		a = new mbyte[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	byteArray::byteArray(mlong size, mbyte defaultValue) {
		super("maven.ByteArray");
		length = size;
		a = new mbyte[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	charArray::charArray(mlong size) {
		super("maven.CharacterArray");
		length = size;
		a = new mchar[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	charArray::charArray(mlong size, mchar defaultValue) {
		super("maven.CharacterArray");
		length = size;
		a = new mchar[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	doubleArray::doubleArray(mlong size) {
		super("maven.DoubleArray");
		length = size;
		a = new mdouble[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	doubleArray::doubleArray(mlong size, mdouble defaultValue) {
		super("maven.DoubleArray");
		length = size;
		a = new mdouble[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	floatArray::floatArray(mlong size) {
		super("maven.FloatArray");
		length = size;
		a = new mfloat[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	floatArray::floatArray(mlong size, mfloat defaultValue) {
		super("maven.FloatArray");
		length = size;
		a = new mfloat[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	intArray::intArray(mlong size) {
		super("maven.IntArray");
		length = size;
		a = new mint[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	intArray::intArray(mlong size, mint defaultValue) {
		super("maven.IntArray");
		length = size;
		a = new mint[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	intArray::intArray(mlong size, mint* values) {
		super("maven.IntArray");
		length = size;
		a = new mint[length];
		for(int i = 0; i < length; ++i)
			a[i] = values[i];
	}
	
	longArray::longArray(mlong size) {
		super("maven.LongArray");
		length = size;
		a = new mlong[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	longArray::longArray(mlong size, mlong defaultValue) {
		super("maven.LongArray");
		length = size;
		a = new mlong[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	shortArray::shortArray(mlong size) {
		super("maven.ShortArray");
		length = size;
		a = new mshort[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	shortArray::shortArray(mlong size, mshort defaultValue) {
		super("maven.ShortArray");
		length = size;
		a = new mshort[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	quadArray::quadArray(mlong size) {
		super("maven.QuadArray");
		length = size;
		a = new mquad[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	quadArray::quadArray(mlong size, mquad defaultValue) {
		super("maven.QuadArray");
		length = size;
		a = new mquad[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	objectArray::objectArray(mlong size) {
		super("maven.ObjectArray");
		length = size;
		a = new maven::Object*[length];
		for(int i = 0; i < length; ++i)
			a[i] = NULL;
	}
	
	objectArray::objectArray(mlong size, maven::Object** assign) {
		super("maven.ObjectArray");
		length = size;
		a = assign;
	}

}
