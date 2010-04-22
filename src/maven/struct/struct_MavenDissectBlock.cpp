/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenDissectBlock.h"
#include "strings.h"

using namespace std;

MavenDissectBlock::MavenDissectBlock() {
	reset();
}

void MavenDissectBlock::reset() {
	unary = "";
	postunary = "";
	forceCast = "";
	original = "";
	processed = "";
	types.clear();
	mutability  = MU_IMPOSSIBLE;
}

void MavenDissectBlock::trim() {
	unary = ::trim(unary);
	postunary = ::trim(postunary);
	forceCast = ::trim(forceCast);
	original = ::trim(original);
	processed = ::trim(processed);
}
