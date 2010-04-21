/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string getConstantType(string& test) {
	// bug #47: '1f' is not valid, must be '1.0f'
	
	// boolean values
	if(test == "true" || test == "false")
		return "boolean";
	
	// test int
	if(strspn(test.c_str(), "+-0123456789") == test.length())
		return "int";
	
	// test byte
	if(test[test.length() - 1] == 'b' && strspn(test.c_str(), "+-0123456789.eb") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "byte";
	}
	if(test[test.length() - 1] == 'B' && strspn(test.c_str(), "+-0123456789.eB") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "byte";
	}
	
	// test char
	if(test[test.length() - 1] == 'c' && strspn(test.c_str(), "+-0123456789.ec") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "char";
	}
	if(test[test.length() - 1] == 'C' && strspn(test.c_str(), "+-0123456789.eC") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "char";
	}
	
	// test int
	if(test[test.length() - 1] == 'i' && strspn(test.c_str(), "+-0123456789.ei") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "int";
	}
	if(test[test.length() - 1] == 'I' && strspn(test.c_str(), "+-0123456789.eI") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "int";
	}
	
	// test short
	if(test[test.length() - 1] == 's' && strspn(test.c_str(), "+-0123456789.es") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "short";
	}
	if(test[test.length() - 1] == 'S' && strspn(test.c_str(), "+-0123456789.eS") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "short";
	}
	
	// test float
	if(test[test.length() - 1] == 'f' && strspn(test.c_str(), "+-0123456789.ef") == test.length())
		return "float";
	if(test[test.length() - 1] == 'F' && strspn(test.c_str(), "+-0123456789.eF") == test.length())
		return "float";
	
	// test double
	if(test[test.length() - 1] == 'd' && strspn(test.c_str(), "+-0123456789.ed") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "double";
	}
	if(test[test.length() - 1] == 'D' && strspn(test.c_str(), "+-0123456789.eD") == test.length()) {
		test = test.substr(0, test.length() - 1);
		return "double";
	}
	
	// test long
	if(test[test.length() - 1] == 'l' && strspn(test.c_str(), "+-0123456789.el") == test.length())
		return "long";
	if(test[test.length() - 1] == 'L' && strspn(test.c_str(), "+-0123456789.eL") == test.length())
		return "long";
	
	// test quad
	if(strspn(test.c_str(), "+-0123456789.e") == test.length())
		return "quad";
	
	// test hexadecimal
	// !C002
	if(test.length() > 2 && test.substr(0, 2) == "0x" &&
	   strspn(test.c_str(), "+-0123456789xabcdefABCDEF") == test.length()) {
		   if(atol(test.c_str()) > 0x80000000)
			   return "long";
		   return "int";
	   }
	
	return "<unknown>";
}
