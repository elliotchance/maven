/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_StringList.h"
#include "struct_MavenCompiler.h"
#include "strings.h"

MavenDocTag filterDoc(MavenCompiler* c, string comment) {
	MavenDocTag r;
	string body = "";
	
	// first check if the tag is infact a doc tag
	if(comment[0] != '*')
		return r;
	
	// locate the tags
	StringList lines = split('\n', comment);
	for(int i = 0; i < lines.length(); ++i) {
		string line = lines[i];
		if(lines[i].find('*') != string::npos)
			line = line.substr(line.find('*') + 1);
		line = trim(line);
		if(line == "*")
			line = "";
		
		// FIXME: put all in
		if(startsWith(line, "@brief"))
			r.tagBrief = line.substr(7);
		else if(startsWith(line, "@since"))
			r.tagSince = line.substr(7);
		else if(startsWith(line, "@version"))
			r.tagSince = line.substr(9);
		else r.body += line + "\n";
	}
	
	// if there is no @brief we have to make one
	if(r.tagBrief == "") {
		for(int i = 0; i < r.body.length(); ++i) {
			char c = r.body[i];
			
			if(c == '.')
				break;
			r.tagBrief += c;
		}
		r.tagBrief += '.';
	}
	
	return r;
}
