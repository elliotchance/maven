/*
 *  md5.h
 *  maven
 *
 */

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
