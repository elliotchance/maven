/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

using namespace std;

StringList StringList::operator =(string str) {
	list.clear();
	list.push_back(str);
	return *this;
}

StringList StringList::setTypes(string str) {
	list.clear();
	StringList split = splitCommas(str);
	for(int i = 0; i < split.length(); ++i)
		list.push_back(split[i]);
	return *this;
}

void StringList::clear() {
	list.clear();
}

StringList::StringList() {
}

void StringList::push(string item) {
	list.push_back(item);
}

int StringList::length() {
	return list.size();
}

string& StringList::operator [](int element) {
	return list[element];
}

string StringList::join(string glue) {
	string r = "";
	for(int i = 0; i < list.size(); ++i) {
		if(i > 0) r += glue;
		r += list[i];
	}
	return r;
}

string StringList::join(string glue, int length) {
	string r = "";
	for(int i = 0; i < length; ++i) {
		if(i > 0) r += glue;
		r += list[i];
	}
	return r;
}

string StringList::join(string glue, int start, int end) {
	string r = "";
	for(int i = start; i <= end; ++i) {
		if(i > start) r += glue;
		r += list[i];
	}
	return r;
}

string StringList::pop() {
	// get last element before destorying it
	string r = list[list.size() - 1];
	list.pop_back();
	return r;
}
