#include "String.h"
#include "Quad.h"
#include "../external/md5.h"
#include "../external/sha1.h"

namespace maven {
	
	String::String() {
		String("");
	}
	
	String::String(const mbyte* newString) {
		len = strlen(newString);
		s = (mbyte*) malloc(len + 1);
		catchMalloc(s, "maven.String");
		std::memmove(s, newString, len);
		s[len] = 0;
	}
	
	mint String::length() {
		return len;
	}
	
	String* String::substring(mint length) {
		mbyte* s2 = (mbyte*) malloc(length + 1);
		strncpy(s2, s, length);
		return new String(s2);
	}
	
	String* String::substring(mint start, mint length) {
		mbyte* s2 = (mbyte*) malloc(length + 1);
		strncpy(s2, s + start, length);
		return new String(s2);
	}
	
	String* String::append(String* str) {
		//if(str == NULL) throw ObjectNilException;
		
		mbyte* newString = new mbyte[len + str->len + 1];
		memmove(newString, s, len);
		memmove(newString + len, str->s, str->len);
		newString[len + str->len] = 0;
		len += str->len;
		
		free(s);
		s = newString;
		return this;
	}
	
	mint String::compare(String* otherString) {
		//if(str == NULL) throw ObjectNilException;
		
		return strcmp(s, otherString->s);
	}
	
	mboolean String::isEmpty() {
		return (len == 0);
	}
	
	void String::erase() {
		len = 0;
		free(s);
	}
	
	mint String::indexOf(maven::String* otherString) {
		//if(str == NULL) throw ObjectNilException;
		
		if(otherString->len > len) return -1;
		for(int i = 0; i < len; ++i) {
			if(s[i] == otherString->s[0]) {
				// make sure all the other characters match in sequence
				for(int j = 1; j < otherString->len; ++j)
					if(s[i + j] != otherString->s[j]) return -1;
				return i;
			}
		}
		return -1;
	}
	
	mboolean String::toBoolean() {
		return length() != 0;
	}
	
	mbyte String::toByte() {
		return (mbyte) atoi(s);
	}
	
	mchar String::toCharacter() {
		return (mchar) atoi(s);
	}
	
	maven::Data* String::toData() {
		maven::Data* d = new maven::Data();
		d->writeString(this);
		return d;
	}
	
	mdouble String::toDouble() {
		return atof(s);
	}
	
	mfloat String::toFloat() {
		return atof(s);
	}
	
	mint String::toInteger() {
		return atoi(s);
	}
	
	mlong String::toLong() {
		return (mlong) atoi(s);
	}
	
	mquad String::toQuad() {
		return (mquad) atof(s);
	}
	
	mshort String::toShort() {
		return (mshort) atoi(s);
	}
	
	maven::String* String::toString() {
		return this;
	}
	
	maven::String* String::valueOf(mboolean value) {
		if(value)
			return new maven::String("true");
		return new maven::String("false");
	}
	
	maven::String* String::valueOf(mbyte value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mchar value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mdouble value) {
		char buf[20];
		std::sprintf(buf, "%g", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mfloat value) {
		char buf[20];
		std::sprintf(buf, "%g", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mint value) {
		char buf[20];
		std::sprintf(buf, "%d", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mlong value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mquad value) {
		char buf[20];
		std::sprintf(buf, "%g", (double) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(mshort value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	mint String::levenshtein(maven::String* otherString) {
		if(len == 0) return otherString->len;
		if(otherString->len == 0) return len;
		
		// good form to declare a TYPEDEF
		typedef std::vector< std::vector<int> > Tmatrix; 
		Tmatrix matrix(len + 1);
		
		// Size the vectors in the 2nd dimension. Unfortunately C++ doesn't
		// allow for allocation on declaration of 2nd dimension of vec of vec
		for (int i = 0; i <= len; i++)
			matrix[i].resize(otherString->len + 1);
		
		// step 2
		for(int i = 0; i <= len; i++) matrix[i][0] = i;
		for(int j = 0; j <= otherString->len; j++) matrix[0][j] = j;
		
		// step 3
		for(int i = 1; i <= len; i++) {
			const char s_i = s[i - 1];
			
			// step 4
			for(int j = 1; j <= otherString->len; j++) {
				const char t_j = otherString->s[j - 1];
				
				// step 5
				int cost;
				if(s_i == t_j) cost = 0;
				else cost = 1;
				
				// step 6
				const int above = matrix[i - 1][j];
				const int left = matrix[i][j - 1];
				const int diag = matrix[i - 1][j - 1];
				int cell = std::min(above + 1, std::min(left + 1, diag + cost));
				
				// step 6A: Cover transposition, in addition to deletion,
				// insertion and substitution. This step is taken from:
				// Berghel, Hal ; Roach, David : "An Extension of Ukkonen's 
				// Enhanced Dynamic Programming ASM Algorithm"
				// (http://www.acm.org/~hlb/publications/asm/asm.html)
				if(i > 2 && j > 2) {
					int trans = matrix[i - 2][j - 2] + 1;
					if(s[i - 2] != t_j) trans++;
					if(s_i != otherString->s[j - 2]) trans++;
					if(cell > trans) cell = trans;
				}
				matrix[i][j] = cell;
			}
		}
		
		// step 7
		return matrix[len][otherString->len];
	}
	
	maven::String* String::md5() {
		MD5_CTX ctx;
		MD5* md5;
		
		// init md5
		md5->MD5Init(&ctx);
		// update with our string
		md5->MD5Update(&ctx, (unsigned char*) s, len);
		
		// create the hash
		unsigned char buff[16] = "";	
		md5->MD5Final((unsigned char*) buff, &ctx);
		
		char asciihash[33];
		int p = 0;
		for(int i = 0; i < 16; i++) {
			std::sprintf((char*) &asciihash[p], "%02x", buff[i]);
			p += 2;
		}	
		asciihash[32] = '\0';
		return new maven::String((char*) asciihash);
	}
	
	maven::String* String::sha1() {
		SHA1 sha;
		unsigned int message_digest[5];
		sha << (char*) s;
		
		if(!sha.Result(message_digest))
			return new String("");
		
		char r[21];
		std::sprintf(r, "%x%x%x%x%x", message_digest[0], message_digest[1], message_digest[2], message_digest[3], message_digest[4]);
		return new maven::String(r);
	}
	
	maven::String* String::operator_plus(maven::String* str2) {
		maven::String* r = new maven::String();
		r->s = this->s;
		r->len = this->len;
		r->append(str2);
		return r;
	}
	
	maven::String* String::operator_plus(mquad str2) {
		maven::String* r = new maven::String();
		r->s = this->s;
		r->len = this->len;
		r->append(maven::String::valueOf(str2));
		return r;
	}
	
	mboolean String::operator_equal(maven::String* str2) {
		return this->compare(str2) == 0;
	}
	
	maven::String* String::operator_assignplus(maven::String* str2) {
		maven::String* temp = this->append(str2);
		// FIXME: free pergatory memory
		s = temp->s;
		len = temp->len;
		return this;
	}
	
}
