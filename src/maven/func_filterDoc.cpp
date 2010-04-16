/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"

MavenDocTag filterDoc(MavenCompiler* c, string comment) {
	MavenDocTag r;
	string body = "";
	
	// first check if the tag is infact a doc tag
	if(comment[0] == '*')
		body = trim(comment.substr(1, comment.length() - 2));
	
	// locate the tags
	StringList lines = split('\n', body);
	for(int i = 0; i < lines.length(); ++i) {
		string line = lines[i];
		if(lines[i].find('*') != string::npos)
			line = line.substr(line.find('*') + 1);
		line = trim(line);
		
		// FIXME: put all in
		if(startsWith(line, "@brief"))
			r.tagBrief = line.substr(7);
		else if(startsWith(line, "@since"))
			r.tagSince = line.substr(7);
		else if(startsWith(line, "@version"))
			r.tagSince = line.substr(9);
		else r.body += line + "\n";
	}
	
	return r;
}
