/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string translateOperatorFunction(string f) {
	char buf[8];
	if(f.length() == 9)
		sprintf(buf, "%X", f[8]);
	else if(f.length() == 10)
		sprintf(buf, "%X%X", f[8], f[9]);
	else if(f.length() == 11)
		sprintf(buf, "%X%X%X", f[8], f[9], f[10]);
	else buf[0] = '\0';
	return "operator_" + string(reinterpret_cast<char*>(buf));
}

string translateOperator(string op) {
	if(op == "===")
		return "==";
	if(op == "!==")
		return "!=";
	return op;
}
