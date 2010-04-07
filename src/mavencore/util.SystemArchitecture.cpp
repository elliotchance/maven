#include "util.SystemArchitecture.h"

// System architecture information

namespace util {

	maven_boolean SystemArchitecture::CPUID(int Function, int bit, char reg) {
		int A, B, C, D;

		#ifdef WIN32
		__asm (
			 "mov %%eax, %4\n"
			 "cpuid\n"
			 "mov %0, %%eax\n"
			 "mov %1, %%ebx\n"
			 "mov %2, %%ecx\n"
			 "mov %3, %%edx\n"
             :"=m"(A), "=m"(B), "=m"(C) ,"=m"(D)
			 :"m"(Function)
			 :"eax", "ebx", "ecx", "edx"
		);
		#else
		__asm {
			mov eax, Function
			cpuid
			mov A, eax
			mov B, ebx
			mov C, ecx
			mov D, edx
		}
		#endif

		if (reg == 'A') {
			std::bitset<32> bits(A);
			return (bits[bit] == 1);
		}

		if (reg == 'B') {
			std::bitset<32> bits(B);
			return (bits[bit] == 1);
		}
	
		if (reg == 'C') {
			std::bitset<32> bits(C);
			return (bits[bit] == 1);
		}

		if (reg == 'D') {
			std::bitset<32> bits(D);
			return (bits[bit] == 1);
		}
	
		return false;
	}
	
	maven_boolean SystemArchitecture::CPUID(int Function, char reg) {
		int A, B, C, D;

		#ifdef WIN32
		asm (
			 "mov %%eax, %4\n\t"
			 "cpuid\n\t"
			 "mov %0, %%eax\n\t"
			 "mov %1, %%ebx\n\t"
			 "mov %2, %%ecx\n\t"
			 "mov %3, %%edx\n\t"
             :"=m"(A), "=m"(B), "=m"(C) ,"=m"(D)
			 :"m"(Function)
			 : "eax", "ebx", "ecx", "edx"
		);
		#else
		__asm {
			mov eax, Function
			cpuid
			mov A, eax
			mov B, ebx
			mov C, ecx
			mov D, edx
		}
		#endif

		if (reg == 'A') return A;
		if (reg == 'B') return B;
		if (reg == 'C') return C;
		if (reg == 'D') return D;
		return 0;
	}
	
	maven_boolean SystemArchitecture::MMX() {
		return CPUID(0x0000001, 23, 'D');
	}

	maven_boolean SystemArchitecture::SSE() {
		return CPUID(0x0000001, 25, 'D');
	}

	maven_boolean SystemArchitecture::SSE2() {
		return CPUID(0x0000001, 26, 'D');
	}
	
	maven_boolean SystemArchitecture::SSE3() {
		return CPUID(0x0000001, 0, 'C');
	}

	maven_boolean SystemArchitecture::SSSE3() {
		return CPUID(0x0000001, 9, 'C');
	}

	maven_boolean SystemArchitecture::SSE4A() {
		return CPUID(0x80000001, 6, 'C');
	}

	maven_boolean SystemArchitecture::SSE41() {
		return CPUID(0x0000001, 19, 'C');
	}

	maven_boolean SystemArchitecture::SSE42() {
		return CPUID(0x0000001, 20, 'C');
	}
	maven_boolean SystemArchitecture::P16BATOMIC() {
		return CPUID(0x0000001, 13, 'C');
	}

	maven_boolean SystemArchitecture::LONGMODE() {
		return CPUID(0x80000001, 29, 'D');
	}
	
}
