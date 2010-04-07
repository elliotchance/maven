/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

using namespace std;

MavenDissectBlock::MavenDissectBlock() {
	reset();
}

void MavenDissectBlock::reset() {
	unary = "";
	postunary = "";
	forceCast = "";
	/*bareword = "";
	entity = "";
	element = "";
	args = "";*/
	original = "";
	processed = "";
	types.clear();
	mutability  = MU_IMPOSSIBLE;
}

void MavenDissectBlock::trim() {
	unary = ::trim(unary);
	postunary = ::trim(postunary);
	forceCast = ::trim(forceCast);
	/*bareword = ::trim(bareword);
	entity = ::trim(entity);
	element = ::trim(element);
	args = ::trim(args);*/
	original = ::trim(original);
	processed = ::trim(processed);
}
