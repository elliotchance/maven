/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

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
