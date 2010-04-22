#include "SystemArchitecture.h"

#include <bitset>

// System architecture information
/** 
* @author Alex <aimmig2@hotmail.com>
* @url http://www.sandpile.org/ia32/cpuid.htm for more information on what each CPUID function does and what
* each bit returned represents
*/


namespace util {

	/**
	 * 3 input CPUID function.
	 *
	 * @brief CPUID(int, int, char) function that returns a single bit from a register specified after running the cpuid function
	 * specificed.
	 *
	 * @return a single bit, specified in the second arugment [bit] from the register specified in the
	 * third arugment [reg] after executing the cpuid function specificed by the first arugment [function].
	 *
	 * @param Function the CPUID function you want to execute, this is inputted with hexadecimal
	 * notation to make reading easier.
	 *
	 * @param bit the bit you want return, inputted in decimal notation range [0 - 31].
	 *
	 * @param reg the register you want to return range ['A', 'B', 'C', 'D'] that corrospond to the x86 
	 * registers EAX, EBX, ECX and EDX.
	 *
	 * Example use, the below function returns true if the CPU supports SSE and false if it doesn't support SSE.
	 *
	 * @code
     * CPUID(0x0000001, 25, 'D'); //returns the 25th bit, from the register EDX after running the cpuid function 0x0000001
	 * @endcode
	 *
	 * @url http://en.wikipedia.org/wiki/CPUID for more information on the CPUID instruction.
	 */
	bool SystemArchitecture::CPUID(int Function, int bit, char reg) {
		int A, B, C, D;

		#ifdef WIN32
		asm (
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

	/**
	* 2 input CPUID function.
	*
	* @brief CPUID(int, char) function that returns a int that contains the contents of the register
	* specificed in the second arugment [reg].
	*
	* @return a int, which corrosponds to the register specificed in the second arugment [reg].
	*
	* @param Function the CPUID function you want to execute, this is inputted with hexadecimal
	* notation to make reading easier.
	*
    * @param reg the register you want to return range ['A', 'B', 'C', 'D'] that corrospond to the x86 
	* registers EAX, EBX, ECX and EDX.
	*
	* Example use, the below function returns the total number of cores on a die
	*
	* @code
	* CPUID(0x00000001, 'A'); //returns the contents of register 'A' [EAX], after running the cpuid function 0x00000001
	* @endcode
	*
	* @url http://en.wikipedia.org/wiki/CPUID for more information on the CPUID instruction. 
	*/
	int SystemArchitecture::CPUID(int Function, char reg) {
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
	
	/**
	 * Returns true if the current cpu supports MMX instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::MMX() {
		return CPUID(0x0000001, 23, 'D');
	}

	/**
	 * Returns true if the current cpu supports SSE instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE() {
		return CPUID(0x0000001, 25, 'D');
	}

	/**
	 * Returns true if the current cpu supports SSE2 instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE2() {
		return CPUID(0x0000001, 26, 'D');
	}
	
	/**
	 * Returns true if the current cpu supports SSE3 instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE3() {
		return CPUID(0x0000001, 0, 'C');
	}
		
	/**
	 * Returns true if the current cpu supports SSSE3 instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSSE3() {
		return CPUID(0x0000001, 9, 'C');
	}

	/**
	 * Returns true if the current cpu supports SSE4A instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE4A() {
		return CPUID(0x80000001, 6, 'C');
	}

	/**
	 * Returns true if the current cpu supports SSE4.1 instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE41() {
		return CPUID(0x0000001, 19, 'C');
	}

	/**
	 * Returns true if the current cpu supports SSE4.2 instructions; otherwise returns false.
	 */
	mboolean SystemArchitecture::SSE42() {
		return CPUID(0x0000001, 20, 'C');
	}

	/**
	 * Returns true if the current cpu supports 16 byte cmp and exchange
	 */
	
	mboolean SystemArchitecture::P16BATOMIC() {				
		return CPUID(0x0000001, 13, 'C');
	}

	/**
	* Returns true if the current cpu supports 64bit instructions
	*/
	mboolean SystemArchitecture::LONGMODE() {
		return CPUID(0x80000001, 29, 'D');
	}
	
	/**
	 * Returns true if the current cpu is multi processor capable, note that a true result from
	 * this does not indicate that there are multi processors in the system just that the cpu is
	 * capable of being used in a multi processor configuration.
	 */
	mboolean SystemArchitecture::multiProcessorCapable() {
		return CPUID(0x80000001, 19, 'D');
	}

	/**
	 * Returns the number cpu's on the die, note that a single package may contain multiple dies
	 * and this will return the results for only one of the dies.
	 */

	mint SystemArchitecture::totalCores() {
		unsigned int ret = CPUID(0x00000001, 'A');

		ret = ret & 15;
		ret = ret >> 1;
		ret = ret - 1;

		return ret;
	}
}
