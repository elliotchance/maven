#include "Data.h"

#include <string>

namespace maven {
	
	Data::Data() {
		super("maven.Data");
		size = 0;
		allocatedSize = 0;
		position = 0;
		head = NULL;
	}
	
	void Data::allocateBytes(mlong bytes) {
		// see if there is enough space left
		if(bytes + size <= allocatedSize) return;
		
		// we have to allocate some more memory
		DataChunk* newChunk = new DataChunk();
		if(head == NULL)
			head = newChunk;
		tail = head;
		
		allocatedSize += MAVEN_DATA_CHUNKSIZE;
	}
	
	mboolean Data::setPosition(mlong pos) {
		if(pos < 0)
			return setPosition(allocatedSize + pos);
			
		if(pos > allocatedSize) return false;
		position = pos;
		return true;
	}
	
	void Data::write(mbyte* data, mlong bytes) {
		std::memmove(tail->chunk + position, data, bytes);
		position += bytes;
	}
	
	void Data::writeBoolean(mboolean data) {
		allocateBytes(sizeof(mboolean));
		write((char*) &data, sizeof(mboolean));
		size += sizeof(mboolean);
	}
	
	void Data::writeByte(mbyte data) {
		allocateBytes(sizeof(mbyte));
		write((char*) &data, sizeof(mbyte));
		size += sizeof(mbyte);
	}
	
	void Data::writeChar(mchar data) {
		allocateBytes(sizeof(mchar));
		write((char*) &data, sizeof(mchar));
		size += sizeof(mchar);
	}
	
	void Data::writeDouble(mdouble data) {
		allocateBytes(sizeof(mdouble));
		write((char*) &data, sizeof(mdouble));
		size += sizeof(mdouble);
	}
	
	void Data::writeFloat(mfloat data) {
		allocateBytes(sizeof(mfloat));
		write((char*) &data, sizeof(mfloat));
		size += sizeof(mfloat);
	}
	
	void Data::writeInt(mint data) {
		allocateBytes(sizeof(mint));
		write((char*) &data, sizeof(mint));
		size += sizeof(mint);
	}
	
	void Data::writeLong(mlong data) {
		allocateBytes(sizeof(mlong));
		write((char*) &data, sizeof(mlong));
		size += sizeof(mlong);
	}
	
	void Data::writeShort(mshort data) {
		allocateBytes(sizeof(mshort));
		write((char*) &data, sizeof(mshort));
		size += sizeof(mshort);
	}
	
	void Data::writeQuad(mquad data) {
		allocateBytes(sizeof(mquad));
		write((char*) &data, sizeof(mquad));
		size += sizeof(mquad);
	}
	
	mboolean Data::readBoolean() {
		mboolean temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mboolean));
		position += sizeof(mboolean);
		return temp;
	}
	
	mbyte Data::readByte() {
		mbyte temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mbyte));
		position += sizeof(mbyte);
		return temp;
	}
	
	mchar Data::readChar() {
		mchar temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mchar));
		position += sizeof(mchar);
		return temp;
	}
	
	mdouble Data::readDouble() {
		mdouble temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mdouble));
		position += sizeof(mdouble);
		return temp;
	}
	
	mfloat Data::readFloat() {
		mfloat temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mfloat));
		position += sizeof(mfloat);
		return temp;
	}
	
	mint Data::readInt() {
		mint temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mint));
		position += sizeof(mint);
		return temp;
	}
	
	mlong Data::readLong() {
		mlong temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mlong));
		position += sizeof(mlong);
		return temp;
	}
	
	mshort Data::readShort() {
		mshort temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mshort));
		position += sizeof(mshort);
		return temp;
	}
	
	mquad Data::readQuad() {
		mquad temp;
		memmove((void*) &temp, tail->chunk + position, sizeof(mquad));
		position += sizeof(mquad);
		return temp;
	}
	
}
