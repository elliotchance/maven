#ifndef MAVENCORE_IO_FILE
#define MAVENCORE_IO_FILE 1

#include "../mavencore.h"
#include "../maven/Data.h"

namespace io {
	
	#define MAVEN_IO_FILE_READ 1
	#define MAVEN_IO_FILE_WRITE 2
	#define MAVEN_IO_FILE_BINARY 3
	
	class File extends maven::Object {
		public_variable std::fstream* f;
		
		// universal methods
		public_constructor File(maven::String* path);
		public_constructor File(maven::String* path, mint mode);
		public_method mboolean isOpen();
		public_method void close();
		public_method mboolean endOfFile();
		
		// reading
		public_method maven::Data* readData();
		public_method maven::String* readLine();
		public_method mboolean readBoolean();
		public_method mbyte readByte();
		public_method mint readInt();
		public_method mchar readChar();
		public_method mfloat readFloat();
		public_method mdouble readDouble();
		public_method mquad readQuad();
		public_method mlong readLong();
		public_method mshort readShort();
		
		// writing
		public_method mboolean writeData(maven::Data* data);
		public_method mboolean writeLine(maven::String* line);
		public_method mboolean writeBoolean(mboolean x);
		public_method mboolean writeByte(mbyte x);
		public_method mboolean writeInt(mint x);
		public_method mboolean writeChar(mchar x);
		public_method mboolean writeFloat(mfloat);
		public_method mboolean writeDouble(mdouble x);
		public_method mboolean writeQuad(mquad x);
		public_method mboolean writeLong(mlong x);
		public_method mboolean writeShort(mshort x);
	};
	
}

#endif
