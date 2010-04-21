#include "io.File.h"

namespace io {
		
	File::File(maven::String* path) {
		File(path, MAVEN_IO_FILE_READ);
	}
	
	File::File(maven::String* path, maven_int mode) {
		super("maven.File");
		catchNilObjectException(path, return);
		catchNilObjectException(mode, return);
		
		f = new std::fstream();
		if(mode == MAVEN_IO_FILE_READ) {
			f->open(path->s, std::fstream::in);
			return;
		}
		if(mode == MAVEN_IO_FILE_WRITE) {
			f->open(path->s, std::fstream::out);
			return;
		}
	}
	
	maven_boolean File::isOpen() {
		return f->is_open();
	}
	
	void File::close() {
		f->close();
	}
	
	maven_boolean File::endOfFile() {
		return f->eof();
	}
	
	maven::String* File::readLine() {
		if(!f->is_open())
			return new maven::String("");
		
		std::string line = "";
		maven_byte c;
		while(!f->eof()) {
			c = f->get();
			if(c == '\n') break;
			line += c;
		}
		return new maven::String(line.c_str());
	}
	
	maven_boolean File::readBoolean() {
		return f->get() != 0;
	}
	
	maven_byte File::readByte() {
		return f->get();
	}
	
	maven::Data* File::readData() {
		maven::Data* data = new maven::Data();
		f->read((char*) &data->size, sizeof(data->size));
		char buffer[MAVEN_DATA_CHUNKSIZE];
		f->read((char*) buffer, data->size);
		
		// move to Data
		data->allocateBytes(data->size);
		data->write((char*) buffer, data->size);
		
		return data;
	}
	
	maven_int File::readInt() {
		maven_int temp;
		f->read((char*) &temp, sizeof(maven_int));
		return temp;
	}
	
	maven_char File::readChar() {
		maven_char temp;
		f->read((char*) &temp, sizeof(maven_char));
		return temp;
	}
	
	maven_float File::readFloat() {
		maven_float temp;
		f->read((char*) &temp, sizeof(maven_float));
		return temp;
	}
	
	maven_double File::readDouble() {
		maven_double temp;
		f->read((char*) &temp, sizeof(maven_double));
		return temp;
	}
	
	maven_quad File::readQuad() {
		maven_quad temp;
		f->read((char*) &temp, sizeof(maven_quad));
		return temp;
	}
	
	maven_long File::readLong() {
		maven_long temp;
		f->read((char*) &temp, sizeof(maven_long));
		return temp;
	}
	
	maven_short File::readShort() {
		maven_short temp;
		f->read((char*) &temp, sizeof(maven_short));
		return temp;
	}
	
	maven_boolean File::writeData(maven::Data* data) {
		if(data == NULL) return false;
		f->write((const char*) &data->size, sizeof(data->size));
		return f->write((const char*) data->tail->chunk, data->size);
	}
	
	maven_boolean File::writeBoolean(maven_boolean x) {
		return f->write((const char*) &x, sizeof(maven_boolean));
	}
	
	maven_boolean File::writeByte(maven_byte x) {
		return f->write((const char*) &x, sizeof(maven_byte));
	}
	
	maven_boolean File::writeInt(maven_int x) {
		return f->write((const char*) &x, sizeof(maven_int));
	}
	
	maven_boolean File::writeChar(maven_char x) {
		return f->write((const char*) &x, sizeof(maven_char));
	}
	
	maven_boolean File::writeFloat(maven_float x) {
		return f->write((const char*) &x, sizeof(maven_float));
	}
	
	maven_boolean File::writeDouble(maven_double x) {
		return f->write((const char*) &x, sizeof(maven_double));
	}
	
	maven_boolean File::writeQuad(maven_quad x) {
		return f->write((const char*) &x, sizeof(maven_quad));
	}
	
	maven_boolean File::writeLong(maven_long x) {
		return f->write((const char*) &x, sizeof(maven_long));
	}
	
	maven_boolean File::writeShort(maven_short x) {
		return f->write((const char*) &x, sizeof(maven_short));
	}
	
	maven_boolean File::writeLine(maven::String* line) {
		if(!f->is_open()) return false;
		f->write(line->s, line->len);
		f->write("\n", 1);
		return true;
	}

}
