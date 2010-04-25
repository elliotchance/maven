/*
 *  sha1.h
 *  maven
 *
 */

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
