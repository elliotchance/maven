/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"

void stripHyphen(string& key, string& value) {
	// check if the key is a '--'
	if(key.substr(0, 2) == "--") {
		// key goes until space or '='
		int i;
		for(i = 2; i < key.length(); ++i)
			if(key[i] == ' ' || key[i] == '=') break;
		
		value = key.substr(i + 1, key.length() - i - 1);
		key = key.substr(2, i - 2);
	} else {
		if(key.length() > 2) {
			value = key.substr(2, key.length() - 1);
			key = key[1];
		} else {
			// some arguments do not require a value
			key = key[1];
			if(key == "c" || key == "e" || key == "h" || key == "K" || key == "r" ||
			   key == "x" || key == "v" || key == "V") value = "";
			else value = "<next>";
		}
	}
}
