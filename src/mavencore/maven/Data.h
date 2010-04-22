#ifndef MAVENCORE_MAVEN_DATA
#define MAVENCORE_MAVEN_DATA 1

#include "../mavencore.h"
#include "../maven/Object.h"

#define MAVEN_DATA_CHUNKSIZE 1024

namespace maven {
	
	struct DataChunk {
		DataChunk* next;
		char chunk[MAVEN_DATA_CHUNKSIZE];
	};
	
	class Data extends maven::Object {
		public_variable readonly mlong size;
		public_variable readonly mlong allocatedSize;
		public_variable readonly mlong position;
		public_variable DataChunk* head;
		public_variable DataChunk* tail;
		
		public_constructor Data();
		
		public_method void allocateBytes(mlong bytes);
		public_method mboolean setPosition(mlong pos);
		
		public_method mboolean readBoolean();
		public_method mbyte readByte();
		public_method mchar readChar();
		public_method mdouble readDouble();
		public_method mfloat readFloat();
		public_method mint readInt();
		public_method mlong readLong();
		public_method mshort readShort();
		public_method mquad readQuad();
		
		public_method void writeBoolean(mboolean data);
		public_method void writeByte(mbyte data);
		public_method void writeChar(mchar data);
		public_method void writeDouble(mdouble data);
		public_method void writeFloat(mfloat data);
		public_method void writeInt(mint data);
		public_method void writeLong(mlong data);
		public_method void writeShort(mshort data);
		public_method void writeQuad(mquad data);
		
		// internal methods
		public_method void write(mbyte* data, mlong bytes);
	};
	
}

#endif
