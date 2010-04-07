/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

using namespace std;

MavenEnumItem::MavenEnumItem() {
	name = "";
	value = 0;
	isDefault = false;
}

// this function will return the value of the default enum it
// if there is no specified default it will return the value of
// the first element
int MavenEnum::getDefaultValue() {
	for(int i = 0; i < items.size(); ++i) {
		if(items[i].isDefault)
			return items[i].value;
	}
	return items[0].value;
}
