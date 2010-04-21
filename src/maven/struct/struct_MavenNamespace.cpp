/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenNamespace.h"

MavenNamespace::MavenNamespace() {
	objects = new MavenObjects();
}

MavenNamespace::~MavenNamespace() {
	// free(objects)
}
