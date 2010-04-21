/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "strings.h"

// this function takes 2 paths and smashes them together
string combinePaths(string path1, string path2, bool includeLastSlash) {
	if(path2 != "" && path2[0] == '/')
		return path2;
	
	// to compinsate for windows paths we swtich the backslash for
	// forward slash
	for(int i = 0; i < path1.length(); ++i)
		if(path1[i] == '\\') path1[i] = '/';
	for(int i = 0; i < path2.length(); ++i)
		if(path2[i] == '\\') path2[i] = '/';
	
	// take off the last slash
	if(path1.at(path1.length() - 1) == '/')
		path1 = path1.substr(0, path1.length() - 1);
	if(path2.at(path2.length() - 1) == '/')
		path2 = path2.substr(0, path2.length() - 1);
	
	StringList p1 = split('/', path1), p2 = split('/', path2);
	for(int i = 0; i < p2.length(); ++i) {
		if(p2[i] == "." || p2[i] == "") {
			// ignore these
		} else if(p2[i] == "..") {
			p1.pop();
		} else p1.push(p2[i]);
	}
	
	if(includeLastSlash)
		return p1.join("/") + "/";
	return p1.join("/");
}
