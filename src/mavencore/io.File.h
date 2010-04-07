#ifndef MAVENCORE_IO_FILE
#define MAVENCORE_IO_FILE 1

#include "mavencoreclean.h"
#include "maven.Data.h"

namespace io {
	
	#define MAVEN_IO_FILE_READ 1
	#define MAVEN_IO_FILE_WRITE 2
	#define MAVEN_IO_FILE_BINARY 3
	
	class File extends maven::Object {
		public_variable std::fstream* f;
		
		// universal methods
		public_constructor File(maven::String* path);
		public_constructor File(maven::String* path, maven_int mode);
		public_method maven_boolean isOpen();
		public_method void close();
		public_method maven_boolean endOfFile();
		
		// reading
		public_method maven::Data* readData();
		public_method maven::String* readLine();
		public_method maven_boolean readBoolean();
		public_method maven_byte readByte();
		public_method maven_int readInt();
		public_method maven_char readChar();
		public_method maven_float readFloat();
		public_method maven_double readDouble();
		public_method maven_quad readQuad();
		public_method maven_long readLong();
		public_method maven_short readShort();
		
		// writing
		public_method maven_boolean writeData(maven::Data* data);
		public_method maven_boolean writeLine(maven::String* line);
		public_method maven_boolean writeBoolean(maven_boolean x);
		public_method maven_boolean writeByte(maven_byte x);
		public_method maven_boolean writeInt(maven_int x);
		public_method maven_boolean writeChar(maven_char x);
		public_method maven_boolean writeFloat(maven_float);
		public_method maven_boolean writeDouble(maven_double x);
		public_method maven_boolean writeQuad(maven_quad x);
		public_method maven_boolean writeLong(maven_long x);
		public_method maven_boolean writeShort(maven_short x);
	};
	
}

#endif
