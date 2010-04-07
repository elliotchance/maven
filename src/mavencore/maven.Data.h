#ifndef MAVENCORE_MAVEN_DATA
#define MAVENCORE_MAVEN_DATA 1

#include "mavencoreclean.h"
#include "maven.Object.h"

#define MAVEN_DATA_CHUNKSIZE 1024

namespace maven {
	
	struct DataChunk {
		DataChunk* next;
		char chunk[MAVEN_DATA_CHUNKSIZE];
	};
	
	class Data extends maven::Object {
		public_variable readonly maven_long size;
		public_variable readonly maven_long allocatedSize;
		public_variable readonly maven_long position;
		public_variable DataChunk* head;
		public_variable DataChunk* tail;
		
		public_constructor Data();
		
		public_method void allocateBytes(maven_long bytes);
		public_method maven_boolean setPosition(maven_long pos);
		
		public_method maven_boolean readBoolean();
		public_method maven_byte readByte();
		public_method maven_char readChar();
		public_method maven_double readDouble();
		public_method maven_float readFloat();
		public_method maven_int readInt();
		public_method maven_long readLong();
		public_method maven_short readShort();
		public_method maven_quad readQuad();
		
		public_method void writeBoolean(maven_boolean data);
		public_method void writeByte(maven_byte data);
		public_method void writeChar(maven_char data);
		public_method void writeDouble(maven_double data);
		public_method void writeFloat(maven_float data);
		public_method void writeInt(maven_int data);
		public_method void writeLong(maven_long data);
		public_method void writeShort(maven_short data);
		public_method void writeQuad(maven_quad data);
		
		// internal methods
		public_method void write(maven_byte* data, maven_long bytes);
	};
	
}

#endif
