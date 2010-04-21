#include "maven.Data.h"

namespace maven {
	
	Data::Data() {
		super("maven.Data");
		size = 0;
		allocatedSize = 0;
		position = 0;
		head = NULL;
	}
	
	void Data::allocateBytes(maven_long bytes) {
		// see if there is enough space left
		if(bytes + size <= allocatedSize) return;
		
		// we have to allocate some more memory
		DataChunk* newChunk = new DataChunk();
		if(head == NULL)
			head = newChunk;
		tail = head;
		
		allocatedSize += MAVEN_DATA_CHUNKSIZE;
	}
	
	maven_boolean Data::setPosition(maven_long pos) {
		if(pos < 0)
			return setPosition(allocatedSize + pos);
			
		if(pos > allocatedSize) return false;
		position = pos;
		return true;
	}
	
	void Data::write(maven_byte* data, maven_long bytes) {
		memmove(tail->chunk + position, data, bytes);
		position += bytes;
	}
	
	void Data::writeBoolean(maven_boolean data) {
		allocateBytes(sizeof(maven_boolean));
		write((char*) &data, sizeof(maven_boolean));
		size += sizeof(maven_boolean);
	}
	
	void Data::writeByte(maven_byte data) {
		allocateBytes(sizeof(maven_byte));
		write((char*) &data, sizeof(maven_byte));
		size += sizeof(maven_byte);
	}
	
	void Data::writeChar(maven_char data) {
		allocateBytes(sizeof(maven_char));
		write((char*) &data, sizeof(maven_char));
		size += sizeof(maven_char);
	}
	
	void Data::writeDouble(maven_double data) {
		allocateBytes(sizeof(maven_double));
		write((char*) &data, sizeof(maven_double));
		size += sizeof(maven_double);
	}
	
	void Data::writeFloat(maven_float data) {
		allocateBytes(sizeof(maven_float));
		write((char*) &data, sizeof(maven_float));
		size += sizeof(maven_float);
	}
	
	void Data::writeInt(maven_int data) {
		allocateBytes(sizeof(maven_int));
		write((char*) &data, sizeof(maven_int));
		size += sizeof(maven_int);
	}
	
	void Data::writeLong(maven_long data) {
		allocateBytes(sizeof(maven_long));
		write((char*) &data, sizeof(maven_long));
		size += sizeof(maven_long);
	}
	
	void Data::writeShort(maven_short data) {
		allocateBytes(sizeof(maven_short));
		write((char*) &data, sizeof(maven_short));
		size += sizeof(maven_short);
	}
	
	void Data::writeQuad(maven_quad data) {
		allocateBytes(sizeof(maven_quad));
		write((char*) &data, sizeof(maven_quad));
		size += sizeof(maven_quad);
	}
	
	maven_boolean Data::readBoolean() {
		maven_boolean temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_boolean));
		position += sizeof(maven_boolean);
		return temp;
	}
	
	maven_byte Data::readByte() {
		maven_byte temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_byte));
		position += sizeof(maven_byte);
		return temp;
	}
	
	maven_char Data::readChar() {
		maven_char temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_char));
		position += sizeof(maven_char);
		return temp;
	}
	
	maven_double Data::readDouble() {
		maven_double temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_double));
		position += sizeof(maven_double);
		return temp;
	}
	
	maven_float Data::readFloat() {
		maven_float temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_float));
		position += sizeof(maven_float);
		return temp;
	}
	
	maven_int Data::readInt() {
		maven_int temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_int));
		position += sizeof(maven_int);
		return temp;
	}
	
	maven_long Data::readLong() {
		maven_long temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_long));
		position += sizeof(maven_long);
		return temp;
	}
	
	maven_short Data::readShort() {
		maven_short temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_short));
		position += sizeof(maven_short);
		return temp;
	}
	
	maven_quad Data::readQuad() {
		maven_quad temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(maven_quad));
		position += sizeof(maven_quad);
		return temp;
	}
	
}
