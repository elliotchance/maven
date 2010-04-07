/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void reverseErrors(MavenCompiler* c, int start, int len) {
	for(int i = start; i < (start + len) / 2; ++i) {
		MavenError temp = c->errors[i];
		c->errors[i] = c->errors[start + len - i - 1];
		c->errors[start + len - i - 1] = temp;
	}
}
