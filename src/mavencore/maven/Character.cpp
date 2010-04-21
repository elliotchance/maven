#include "Character.h"

namespace maven {
	
	Character::Character() {
		super("maven.Character");
		value = 0;
	}
	
	Character::Character(maven_char newValue) {
		super("maven.Character");
		value = newValue;
	}
	
	maven::String* Character::toString() {
		return maven::String::valueOf(value);
	}

}
