#include "Character.h"

namespace maven {
	
	Character::Character() {
		super("maven.Character");
		value = 0;
	}
	
	Character::Character(mchar newValue) {
		super("maven.Character");
		value = newValue;
	}
	
	maven::String* Character::toString() {
		return maven::String::valueOf(value);
	}

}
