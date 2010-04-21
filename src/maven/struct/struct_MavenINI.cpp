/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenINI.h"

using namespace std;

MavenINI::MavenINI() {
}

bool MavenINI::setKey(string key, string value) {
	// bug #50: check if the key exists
	MavenINIPair p;
	p.k = key;
	p.v = value;
	ini.push_back(p);
	return true;
}

string MavenINI::getKey(string key) {
	for(int i = 0; i < ini.size(); ++i) {
		if(ini[i].k == key)
			return ini[i].v;
	}
	return "";
}
