#include "maven.String.h"
#include "maven.Quad.h"

namespace maven {
	
	String::String() {
		String("");
	}
	
	String::String(const maven_byte* newString) {
		len = strlen(newString);
		s = (maven_byte*) malloc(len + 1);
		catchMalloc(s, "maven.String");
		std::memmove(s, newString, len);
		s[len] = 0;
	}
	
	maven_int String::length() {
		return len;
	}
	
	String* String::substring(maven_int length) {
		maven_byte* s2 = (maven_byte*) malloc(length + 1);
		strncpy(s2, s, length);
		return new String(s2);
	}
	
	String* String::substring(maven_int start, maven_int length) {
		maven_byte* s2 = (maven_byte*) malloc(length + 1);
		strncpy(s2, s + start, length);
		return new String(s2);
	}
	
	String* String::append(String* str) {
		//if(str == NULL) throw ObjectNilException;
		
		maven_byte* newString = new maven_byte[len + str->len + 1];
		memmove(newString, s, len);
		memmove(newString + len, str->s, str->len);
		newString[len + str->len] = 0;
		len += str->len;
		
		free(s);
		s = newString;
		return this;
	}
	
	maven_int String::compare(String* otherString) {
		//if(str == NULL) throw ObjectNilException;
		
		return strcmp(s, otherString->s);
	}
	
	maven_boolean String::isEmpty() {
		return (len == 0);
	}
	
	void String::erase() {
		len = 0;
		free(s);
	}
	
	maven_int String::indexOf(maven::String* otherString) {
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
	
	maven_boolean String::toBoolean() {
		return length() != 0;
	}
	
	maven_byte String::toByte() {
		return (maven_byte) atoi(s);
	}
	
	maven_char String::toCharacter() {
		return (maven_char) atoi(s);
	}
	
	maven::Data* String::toData() {
		// bug #49: export as Data
		return new maven::Data();
	}
	
	maven_double String::toDouble() {
		return atof(s);
	}
	
	maven_float String::toFloat() {
		return atof(s);
	}
	
	maven_int String::toInteger() {
		return atoi(s);
	}
	
	maven_long String::toLong() {
		return (maven_long) atoi(s);
	}
	
	maven_quad String::toQuad() {
		return (maven_quad) atof(s);
	}
	
	maven_short String::toShort() {
		return (maven_short) atoi(s);
	}
	
	maven::String* String::toString() {
		return this;
	}
	
	maven::String* String::valueOf(maven_boolean value) {
		if(value)
			return new maven::String("true");
		return new maven::String("false");
	}
	
	maven::String* String::valueOf(maven_byte value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_char value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_double value) {
		char buf[20];
		std::sprintf(buf, "%g", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_float value) {
		char buf[20];
		std::sprintf(buf, "%g", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_int value) {
		char buf[20];
		std::sprintf(buf, "%d", value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_long value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_quad value) {
		char buf[20];
		std::sprintf(buf, "%g", (double) value);
		return new maven::String(buf);
	}
	
	maven::String* String::valueOf(maven_short value) {
		char buf[20];
		std::sprintf(buf, "%d", (int) value);
		return new maven::String(buf);
	}
	
	maven_int String::levenshtein(maven::String* otherString) {
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
	
	typedef unsigned char *POINTER;
	typedef struct {
		unsigned long state[4];   	  /* state (ABCD) */
		unsigned long count[2]; 	  /* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];	  /* input buffer */
	} MD5_CTX;
	
	class MD5 {
		private:
			void MD5Transform(unsigned long state[4], unsigned char block[64]);
			void Encode(unsigned char*, unsigned long*, unsigned int);
			void Decode(unsigned long*, unsigned char*, unsigned int);
			void MD5_memcpy(POINTER, POINTER, unsigned int);
			void MD5_memset(POINTER, int, unsigned int);
			
		public:
			void MD5Init(MD5_CTX*);
			void MD5Update(MD5_CTX*, unsigned char*, unsigned int);
			void MD5Final(unsigned char[16], MD5_CTX*);
			
			MD5() {};
	};
	
	// Constants for MD5Transform routine.
	#define S11 7
	#define S12 12
	#define S13 17
	#define S14 22
	#define S21 5
	#define S22 9
	#define S23 14
	#define S24 20
	#define S31 4
	#define S32 11
	#define S33 16
	#define S34 23
	#define S41 6
	#define S42 10
	#define S43 15
	#define S44 21
	
	static unsigned char PADDING[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	
	/* F, G, H and I are basic MD5 functions. */
	#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
	#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
	#define H(x, y, z) ((x) ^ (y) ^ (z))
	#define I(x, y, z) ((y) ^ ((x) | (~z)))
	
	/* ROTATE_LEFT rotates x left n bits. */
	#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
	//#define ROTATE_LEFT(x, n) (((x) << (n)) | (( (UINT32) x) >> (32-(n))))
	
	/*
	 FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	 Rotation is separate from addition to prevent recomputation.
	 */
	#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + (unsigned long)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
		
	#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + (unsigned long)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
	#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + (unsigned long)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
	#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + (unsigned long)(ac); \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
	
	/* MD5 initialization. Begins an MD5 operation, writing a new context. */
	void MD5::MD5Init(MD5_CTX* context) {
		context->count[0] = context->count[1] = 0;
		context->state[0] = 0x67452301;
		context->state[1] = 0xefcdab89;
		context->state[2] = 0x98badcfe;
		context->state[3] = 0x10325476;
	}
	
	/*
	 MD5 block update operation. Continues an MD5 message-digest
	 operation, processing another message block, and updating the
	 context.
	 */
	void MD5::MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputLen) {
		unsigned int i, index, partLen;
		
		/* Compute number of chars mod 64 */
		index = (unsigned int) ((context->count[0] >> 3) & 0x3F);
		
		/* Update number of bits */
		if((context->count[0] += ((unsigned long) inputLen << 3)) < ((unsigned long)inputLen << 3))
			context->count[1]++;
		
		context->count[1] += ((unsigned long) inputLen >> 29);
		partLen = 64 - index;
		
		/*
		 * Transform as many times as possible.
		 */
		if(inputLen >= partLen) {
			MD5_memcpy((POINTER) &context->buffer[index], (POINTER) input, partLen);
			MD5Transform(context->state, context->buffer);
			for(i = partLen; i + 63 < inputLen; i += 64)
				MD5Transform(context->state, &input[i]);
			index = 0;
		} else i = 0;
		
		/* Buffer remaining input */
		MD5_memcpy((POINTER) &context->buffer[index], (POINTER) &input[i], inputLen-i);
	}
	
	/*
	 * MD5 finalization. Ends an MD5 message-digest operation, writing the
	 * the message digest and zeroizing the context.
	 */
	void MD5::MD5Final(unsigned char digest[16], MD5_CTX* context) {
		unsigned char bits[8];
		unsigned int index, padLen;
		
		/* Save number of bits */
		Encode(bits, context->count, 8);
		
		/* 
		 * Pad out to 56 mod 64.
		 */
		index = (unsigned int) ((context->count[0] >> 3) & 0x3f);
		padLen = (index < 56) ? (56 - index) : (120 - index);
		MD5Update(context, PADDING, padLen);
		
		/* Append length (before padding) */
		MD5Update(context, bits, 8);
		
		/* Store state in digest */
		Encode(digest, context->state, 16);
		
		/*
		 * Zeroize sensitive information.
		 */
		MD5_memset((POINTER) context, 0, sizeof(*context));
	}
	
	/*
	 * MD5 basic transformation. Transforms state based on block.
	 */
	void MD5::MD5Transform(unsigned long state[4], unsigned char block[64]) {
		unsigned long a = state[0], b = state[1], c = state[2], d = state[3], x[16];
		Decode(x, block, 64);
		
		/* Round 1 */
		FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
		FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
		FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
		FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
		FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
		FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
		FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
		FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
		FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
		FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
		FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
		FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
		FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
		FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
		FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
		FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
		
		/* Round 2 */
		GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
		GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
		GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
		GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
		GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
		GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
		GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
		GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
		GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
		GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
		GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
		
		GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
		GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
		GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
		GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
		GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
		
		/* Round 3 */
		HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
		HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
		HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
		HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
		HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
		HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
		HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
		HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
		HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
		HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
		HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
		HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
		HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
		HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
		HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
		HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
		
		/* Round 4 */
		II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
		II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
		II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
		II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
		II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
		II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
		II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
		II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
		II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
		II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
		II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
		II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
		II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
		II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
		II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
		II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
		
		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;
		
		/* 
		 * Zeroize sensitive information.
		 */
		MD5_memset((POINTER) x, 0, sizeof(x));
	}
	
	/* 
	 * Encodes input (unsigned long int) into output (unsigned char). Assumes len is
	 * a multiple of 4.
	 */
	void MD5::Encode(unsigned char *output, unsigned long *input, unsigned int len) {
		unsigned int i, j;
		for(i = 0, j = 0; j < len; i++, j += 4) {
			output[j] = (unsigned char) (input[i] & 0xff);
			output[j+1] = (unsigned char) ((input[i] >> 8) & 0xff);
			output[j+2] = (unsigned char) ((input[i] >> 16) & 0xff);
			output[j+3] = (unsigned char) ((input[i] >> 24) & 0xff);
		}
	}
	
	/*
	 * Decodes input (unsigned char) into output (unsigned long int). Assumes len is
	 * a multiple of 4.
	 */
	void MD5::Decode(unsigned long *output, unsigned char *input, unsigned int len) {
		unsigned int i, j;
		for (i = 0, j = 0; j < len; i++, j += 4)
			output[i] = ((unsigned int) input[j]) | 
				(((unsigned int) input[j + 1]) << 8) |
				(((unsigned int) input[j + 2]) << 16) |
				(((unsigned int) input[j + 3]) << 24);
	}
	
	/*
	 * Note: Replace "for loop" with standard memcpy if possible.
	 */
	void MD5::MD5_memcpy(POINTER output, POINTER input, unsigned int len) {
		unsigned int i;
		for(i = 0; i < len; i++)
			output[i] = input[i];
	}
	
	/*
	 * Note: Replace "for loop" with standard memset if possible.
	 */
	void MD5::MD5_memset(POINTER output, int value, unsigned int len) {
		unsigned int i;
		for (i = 0; i < len; i++)
			((char*) output)[i] = (char) value;
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
	
	class SHA1 {
		public:	
			SHA1();
			void Reset();
			bool Result(unsigned int* message_digest_array);
			void Input(const unsigned char* message_array, unsigned int length);
			void Input(const char* message_array, unsigned int length);
			void Input(unsigned char message_element);
			void Input(char message_element);
			SHA1& operator <<(const char* message_array);
			SHA1& operator <<(const unsigned char* message_array);
			SHA1& operator <<(const char message_element);
			SHA1& operator <<(const unsigned char message_element);
			
		private:
			void ProcessMessageBlock();
			void PadMessage();
			inline unsigned int CircularShift(int bits, unsigned int word);
			
			unsigned int H[5];                      // Message digest buffers
			unsigned int Length_Low;                // Message length in bits
			unsigned int Length_High;               // Message length in bits
			unsigned char Message_Block[64];        // 512-bit message blocks
			int Message_Block_Index;        // Index into message block array
			bool Computed;                  // Is the digest computed?
			bool Corrupted;                 // Is the message digest corruped?
			
	};
	
	SHA1::SHA1() {
		Reset();
	}
	
	void SHA1::Reset() {
		Length_Low          = 0;
		Length_High         = 0;
		Message_Block_Index = 0;
		
		H[0]        = 0x67452301;
		H[1]        = 0xEFCDAB89;
		H[2]        = 0x98BADCFE;
		H[3]        = 0x10325476;
		H[4]        = 0xC3D2E1F0;
		
		Computed    = false;
		Corrupted   = false;
	}
	
	bool SHA1::Result(unsigned int* message_digest_array) {
		int i;

		if(Corrupted) return false;
		if(!Computed) {
			PadMessage();
			Computed = true;
		}
		for(i = 0; i < 5; i++)
			message_digest_array[i] = H[i];
		
		return true;
	}
	
	void SHA1::Input(const unsigned char* message_array, unsigned int length) {
		if(!length) return;
		if(Computed || Corrupted) {
			Corrupted = true;
			return;
		}
		
		while(length-- && !Corrupted) {
			Message_Block[Message_Block_Index++] = (*message_array & 0xFF);
			
			Length_Low += 8;
			Length_Low &= 0xFFFFFFFF;               // Force it to 32 bits
			if (Length_Low == 0) {
				Length_High++;
				Length_High &= 0xFFFFFFFF;          // Force it to 32 bits
				if(Length_High == 0)
					Corrupted = true;               // Message is too long
			}
			
			if(Message_Block_Index == 64)
				ProcessMessageBlock();
			message_array++;
		}
	}
	
	void SHA1::Input(const char* message_array, unsigned int length) {
		Input((unsigned char*) message_array, length);
	}
	
	void SHA1::Input(unsigned char message_element) {
		Input(&message_element, 1);
	}
	
	void SHA1::Input(char message_element) {
		Input((unsigned char*) &message_element, 1);
	}
	
	void SHA1::ProcessMessageBlock() {
		const unsigned int K[] =    {               // Constants defined for SHA-1
			0x5A827999,
			0x6ED9EBA1,
			0x8F1BBCDC,
			0xCA62C1D6
		};
		int     t;                          // Loop counter
		unsigned int    temp;                       // Temporary word value
		unsigned int    W[80];                      // Word sequence
		unsigned int    A, B, C, D, E;              // Word buffers
		
		// Initialize the first 16 words in the array W
		for(t = 0; t < 16; t++) {
			W[t] = ((unsigned int) Message_Block[t * 4]) << 24;
			W[t] |= ((unsigned int) Message_Block[t * 4 + 1]) << 16;
			W[t] |= ((unsigned int) Message_Block[t * 4 + 2]) << 8;
			W[t] |= ((unsigned int) Message_Block[t * 4 + 3]);
		}
		
		for(t = 16; t < 80; t++)
			W[t] = CircularShift(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);
		
		A = H[0];
		B = H[1];
		C = H[2];
		D = H[3];
		E = H[4];
		
		for(t = 0; t < 20; t++) {
			temp = CircularShift(5, A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
			temp &= 0xFFFFFFFF;
			E = D;
			D = C;
			C = CircularShift(30, B);
			B = A;
			A = temp;
		}
		
		for(t = 20; t < 40; t++) {
			temp = CircularShift(5, A) + (B ^ C ^ D) + E + W[t] + K[1];
			temp &= 0xFFFFFFFF;
			E = D;
			D = C;
			C = CircularShift(30, B);
			B = A;
			A = temp;
		}
		
		for(t = 40; t < 60; t++) {
			temp = CircularShift(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
			temp &= 0xFFFFFFFF;
			E = D;
			D = C;
			C = CircularShift(30, B);
			B = A;
			A = temp;
		}
		
		for(t = 60; t < 80; t++) {
			temp = CircularShift(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
			temp &= 0xFFFFFFFF;
			E = D;
			D = C;
			C = CircularShift(30, B);
			B = A;
			A = temp;
		}
		
		H[0] = (H[0] + A) & 0xFFFFFFFF;
		H[1] = (H[1] + B) & 0xFFFFFFFF;
		H[2] = (H[2] + C) & 0xFFFFFFFF;
		H[3] = (H[3] + D) & 0xFFFFFFFF;
		H[4] = (H[4] + E) & 0xFFFFFFFF;
		
		Message_Block_Index = 0;
	}
	
	void SHA1::PadMessage() {
		/*
		 *  Check to see if the current message block is too small to hold
		 *  the initial padding bits and length.  If so, we will pad the
		 *  block, process it, and then continue padding into a second block.
		 */
		if (Message_Block_Index > 55) {
			Message_Block[Message_Block_Index++] = 0x80;
			while(Message_Block_Index < 64)
				Message_Block[Message_Block_Index++] = 0;
			ProcessMessageBlock();
			while(Message_Block_Index < 56)
				Message_Block[Message_Block_Index++] = 0;
		} else {
			Message_Block[Message_Block_Index++] = 0x80;
			while(Message_Block_Index < 56)
				Message_Block[Message_Block_Index++] = 0;
		}
		
		/*
		 *  Store the message length as the last 8 octets
		 */
		Message_Block[56] = (Length_High >> 24) & 0xFF;
		Message_Block[57] = (Length_High >> 16) & 0xFF;
		Message_Block[58] = (Length_High >> 8) & 0xFF;
		Message_Block[59] = (Length_High) & 0xFF;
		Message_Block[60] = (Length_Low >> 24) & 0xFF;
		Message_Block[61] = (Length_Low >> 16) & 0xFF;
		Message_Block[62] = (Length_Low >> 8) & 0xFF;
		Message_Block[63] = (Length_Low) & 0xFF;
		
		ProcessMessageBlock();
	}
	
	unsigned int SHA1::CircularShift(int bits, unsigned int word) {
		return ((word << bits) & 0xFFFFFFFF) | ((word & 0xFFFFFFFF) >> (32-bits));
	}
	
	SHA1& SHA1::operator <<(const char *message_array) {
		const char *p = message_array;
		while(*p) {
			Input(*p);
			p++;
		}
		return *this;
	}
	
	SHA1& SHA1::operator <<(const unsigned char *message_array) {
		const unsigned char *p = message_array;
		while(*p) {
			Input(*p);
			p++;
		}
		return *this;
	}
	
	SHA1& SHA1::operator <<(const char message_element) {
		Input((unsigned char*) &message_element, 1);
		return *this;
	}
	
	SHA1& SHA1::operator <<(const unsigned char message_element) {
		Input(&message_element, 1);
		return *this;
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
		return this->append(str2);
	}
	
	maven::String* String::operator_plus(maven_quad str2) {
		return this->append(maven::String::valueOf(str2));
	}
	
	maven_boolean String::operator_equal(maven::String* str2) {
		return this->compare(str2) == 0;
	}
	
}
