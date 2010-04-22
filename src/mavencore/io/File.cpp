#include "../io/File.h"

#include <fstream>

namespace io {
		
	File::File(maven::String* path) {
		File(path, MAVEN_IO_FILE_READ);
	}
	
	File::File(maven::String* path, mint mode) {
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
	
	mboolean File::isOpen() {
		return f->is_open();
	}
	
	void File::close() {
		f->close();
	}
	
	mboolean File::endOfFile() {
		return f->eof();
	}
	
	maven::String* File::readLine() {
		if(!f->is_open())
			return new maven::String("");
		
		std::string line = "";
		mbyte c;
		while(!f->eof()) {
			c = f->get();
			if(c == '\n') break;
			line += c;
		}
		return new maven::String(line.c_str());
	}
	
	mboolean File::readBoolean() {
		return f->get() != 0;
	}
	
	mbyte File::readByte() {
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
	
	mint File::readInt() {
		mint temp;
		f->read((char*) &temp, sizeof(mint));
		return temp;
	}
	
	mchar File::readChar() {
		mchar temp;
		f->read((char*) &temp, sizeof(mchar));
		return temp;
	}
	
	mfloat File::readFloat() {
		mfloat temp;
		f->read((char*) &temp, sizeof(mfloat));
		return temp;
	}
	
	mdouble File::readDouble() {
		mdouble temp;
		f->read((char*) &temp, sizeof(mdouble));
		return temp;
	}
	
	mquad File::readQuad() {
		mquad temp;
		f->read((char*) &temp, sizeof(mquad));
		return temp;
	}
	
	mlong File::readLong() {
		mlong temp;
		f->read((char*) &temp, sizeof(mlong));
		return temp;
	}
	
	mshort File::readShort() {
		mshort temp;
		f->read((char*) &temp, sizeof(mshort));
		return temp;
	}
	
	mboolean File::writeData(maven::Data* data) {
		if(data == NULL) return false;
		f->write((const char*) &data->size, sizeof(data->size));
		return f->write((const char*) data->tail->chunk, data->size);
	}
	
	mboolean File::writeBoolean(mboolean x) {
		return f->write((const char*) &x, sizeof(mboolean));
	}
	
	mboolean File::writeByte(mbyte x) {
		return f->write((const char*) &x, sizeof(mbyte));
	}
	
	mboolean File::writeInt(mint x) {
		return f->write((const char*) &x, sizeof(mint));
	}
	
	mboolean File::writeChar(mchar x) {
		return f->write((const char*) &x, sizeof(mchar));
	}
	
	mboolean File::writeFloat(mfloat x) {
		return f->write((const char*) &x, sizeof(mfloat));
	}
	
	mboolean File::writeDouble(mdouble x) {
		return f->write((const char*) &x, sizeof(mdouble));
	}
	
	mboolean File::writeQuad(mquad x) {
		return f->write((const char*) &x, sizeof(mquad));
	}
	
	mboolean File::writeLong(mlong x) {
		return f->write((const char*) &x, sizeof(mlong));
	}
	
	mboolean File::writeShort(mshort x) {
		return f->write((const char*) &x, sizeof(mshort));
	}
	
	mboolean File::writeLine(maven::String* line) {
		if(!f->is_open()) return false;
		f->write(line->s, line->len);
		f->write("\n", 1);
		return true;
	}

}
