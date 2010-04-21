/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenPair.h"

using namespace std;

MavenPair::MavenPair(string k, string v) {
	key = k;
	value = v;
}
