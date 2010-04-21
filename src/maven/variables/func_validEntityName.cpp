/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

/**
 * This function will validate a given entity name. The only allowed characters
 * are 0-9, a-z, A-Z and underscore (_) and is not allowed to start with a
 * number.
 */
bool validEntityName(string name) {
	if(!name.length())
		return false;
	if(name[0] > '0' && name[0] < '9')
		return false;
	return strspn(name.c_str(), "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_") == name.length();
}
