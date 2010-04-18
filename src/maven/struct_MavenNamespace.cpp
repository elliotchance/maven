/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

MavenNamespace::MavenNamespace() {
	objects = new MavenObjects();
}

MavenNamespace::~MavenNamespace() {
	// free(objects)
}
