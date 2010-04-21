/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenNamespaces.h"
#include "struct_MavenNamespace.h"

MavenNamespaces::MavenNamespaces() {
}

int MavenNamespaces::length() {
	return namespaces.size();
}

MavenNamespace& MavenNamespaces::operator [](int element) {
	return namespaces[element];
}

MavenNamespace& MavenNamespaces::at(int element) {
	return namespaces[element];
}

void MavenNamespaces::push(MavenNamespace* ns) {
	namespaces.push_back(*ns);
}
