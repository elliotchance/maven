#include "Dictionary.h"

namespace maven {
	
	Dictionary::Dictionary() {
		d = NULL;
		len = 0;
	}
	
	mint Dictionary::length() {
		return len;
	}
	
	mboolean Dictionary::keyExists(maven::Object* key) {
		// bug #48: needs to be completed
		catchNilObjectException(key, return false);
		//if(!strcmp(d->key->s, key->s)) return true;
		return false;
	}
	
	mboolean Dictionary::setValue(maven::Object* key, maven::Object* value) {
		catchNilObjectException(key, return false);
		catchNilObjectException(value, return false);
		
		// if the key already exists, just update the value
		DictionaryItem* cursor = d;
		while(cursor != NULL) {
			if(!strcmp(cursor->key->toString()->s, key->toString()->s)) {
				cursor->value = value;
				return true;
			}
			cursor = cursor->next;
		}
		
		// this means the item wasn't found, stick it on the end of the stack
		++len;
		if(d == NULL) {
			d = new DictionaryItem(key, value);
			last = d;
			return true;
		}
		
		last->next = new DictionaryItem(key, value);
		last = last->next;
		return true;
	}
	
	maven::Object* Dictionary::getValue(maven::Object* key) {
		catchNilObjectException(key, return new maven::Object());
		
		DictionaryItem* cursor = d;
		while(cursor != NULL) {
			if(!strcmp(cursor->key->toString()->s, key->toString()->s))
				return cursor->value;
			cursor = cursor->next;
		}
		return new maven::Object();
	}
	
}
