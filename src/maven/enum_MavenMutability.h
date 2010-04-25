/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_ENUM_MAVENMUTABILITY_H
#define _MAVEN_ENUM_MAVENMUTABILITY_H 1

#include "maven.h"

/**
 * When dissecting an entity this lets the parent dissector know if the left have side can be assigned.
 * Usually this will be MM_OK, but in cases of 'constant', 'constant' variables it may be protected and
 * hence MU_CONSTANT. Entityies that are not storage mechanisms are given MU_IMPOSSIBLE, like:
 * @code
 * myFunction() = 5;
 * @endcode
 */
enum MavenMutability {
	MU_OK = 0,
	MU_CONSTANT = 1,
	MU_IMPOSSIBLE = 2
};

#endif
