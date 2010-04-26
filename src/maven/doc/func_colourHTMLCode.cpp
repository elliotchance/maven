/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "keywords.h"

string colourHTMLCode(MavenCompiler* c, string input) {
	string r = "<pre style=\"border: dashed 2px #CCCCCC; padding: 3px; background-color: #EEEEEE\">";
	char ch;
	int tabSize = 4;   // the number of spaces in a tab
	string keyword = "";
	
	for(int i = 0; i < input.length(); ++i) {
		ch = input[i];
		
		// comments
		if(ch == '/') {
			// single line
			if(input[i + 1] == '/') {
				r += "<font color=\"#009900\">";
				for(; i < input.length(); ++i) {
					if(input[i] == '\n')
						break;
					r += input[i];
				}
				r += "</font>\n";
				continue;
			}
			
			// multi line
			if(input[i + 1] == '*') {
				r += "<font color=\"#009900\">";
				for(; i < input.length(); ++i) {
					if(input[i] == '*' && input[i + 1] == '/')
						break;
					r += input[i];
				}
				++i;
				r += "*/</font>";
				continue;
			}
		}
		
		// strings
		if(ch == '"') {
			r += "<font color=\"#FF0000\">\"";
			++i;
			for(; i < input.length(); ++i) {
				ch = input[i];
				
				if(ch == '"')
					break;
				r += ch;
			}
			r += "\"</font>";
			continue;
		}
		
		if(isspace(ch)) {
			if(isKeyword(c, keyword)) {
				r += "<font color=\"#0000CC\">" + keyword + "</font>";
			} else r += keyword;
			keyword = "";
			r += ch;
		} else keyword += ch;
		
	}
	
	return r + "</pre>";
}
