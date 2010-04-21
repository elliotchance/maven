#include "Array.h"

namespace maven {
	
	Array::Array() {
		super("maven.Array");
	}
	
	booleanArray::booleanArray(maven_long size) {
		super("maven.BooleanArray");
		length = size;
		a = new maven_boolean[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	booleanArray::booleanArray(maven_long size, maven_boolean defaultValue) {
		super("maven.BooleanArray");
		length = size;
		a = new maven_boolean[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	byteArray::byteArray(maven_long size) {
		super("maven.ByteArray");
		length = size;
		a = new maven_byte[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	byteArray::byteArray(maven_long size, maven_byte defaultValue) {
		super("maven.ByteArray");
		length = size;
		a = new maven_byte[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	charArray::charArray(maven_long size) {
		super("maven.CharacterArray");
		length = size;
		a = new maven_char[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	charArray::charArray(maven_long size, maven_char defaultValue) {
		super("maven.CharacterArray");
		length = size;
		a = new maven_char[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	doubleArray::doubleArray(maven_long size) {
		super("maven.DoubleArray");
		length = size;
		a = new maven_double[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	doubleArray::doubleArray(maven_long size, maven_double defaultValue) {
		super("maven.DoubleArray");
		length = size;
		a = new maven_double[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	floatArray::floatArray(maven_long size) {
		super("maven.FloatArray");
		length = size;
		a = new maven_float[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	floatArray::floatArray(maven_long size, maven_float defaultValue) {
		super("maven.FloatArray");
		length = size;
		a = new maven_float[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	intArray::intArray(maven_long size) {
		super("maven.IntArray");
		length = size;
		a = new maven_int[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	intArray::intArray(maven_long size, maven_int defaultValue) {
		super("maven.IntArray");
		length = size;
		a = new maven_int[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	intArray::intArray(maven_long size, maven_int* values) {
		super("maven.IntArray");
		length = size;
		a = new maven_int[length];
		for(int i = 0; i < length; ++i)
			a[i] = values[i];
	}
	
	longArray::longArray(maven_long size) {
		super("maven.LongArray");
		length = size;
		a = new maven_long[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	longArray::longArray(maven_long size, maven_long defaultValue) {
		super("maven.LongArray");
		length = size;
		a = new maven_long[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	shortArray::shortArray(maven_long size) {
		super("maven.ShortArray");
		length = size;
		a = new maven_short[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	shortArray::shortArray(maven_long size, maven_short defaultValue) {
		super("maven.ShortArray");
		length = size;
		a = new maven_short[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	quadArray::quadArray(maven_long size) {
		super("maven.QuadArray");
		length = size;
		a = new maven_quad[length];
		for(int i = 0; i < length; ++i)
			a[i] = 0;
	}
	
	quadArray::quadArray(maven_long size, maven_quad defaultValue) {
		super("maven.QuadArray");
		length = size;
		a = new maven_quad[length];
		for(int i = 0; i < length; ++i)
			a[i] = defaultValue;
	}
	
	objectArray::objectArray(maven_long size) {
		super("maven.ObjectArray");
		length = size;
		a = new maven::Object*[length];
		for(int i = 0; i < length; ++i)
			a[i] = NULL;
	}
	
	objectArray::objectArray(maven_long size, maven::Object** assign) {
		super("maven.ObjectArray");
		length = size;
		a = assign;
	}

}
