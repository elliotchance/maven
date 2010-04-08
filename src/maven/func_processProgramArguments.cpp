/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@mavenlang.com>.
 */

#include "maven.h"
#include "compiler_strings.h"
#include "compiler_init.h"

void processProgramArguments(MavenCompiler* c, int argc, char** argv) {
	c->option_base_path = string(argv[0]).substr(0, strlen(argv[0]) - 6);
	
	// if there is no arguments we need to explain to the user
	if(argc == 1)
		usage();
	
	// read arguments
	for(int i = 1; i < argc; ++i) {
		if(argv[i][0] == '-') {
			string value = "";
			string key = argv[i];
			stripHyphen(key, value);
			if(value == "<next>")
				value = argv[++i];
			
			     if(key == "c") c->option_c = true;
			else if(key == "e") c->option_e = true;
			else if(key == "h") c->option_h = true;
			else if(key == "i") c->option_i = value;
			else if(key == "K") c->option_K = true;
			else if(key == "n") c->option_n = value;
			else if(key == "o") c->option_o = value;
			else if(key == "r") c->option_r = true;
			else if(key == "s") c->option_s = atoi(value.c_str());
			else if(key == "v") c->option_v = true;
			else if(key == "V") c->option_V = true;
			else if(key == "w") c->option_w = value;
			else if(key == "W") c->option_W = value;
			else if(key == "x") c->option_x = true;
			else if(key == "doc-sql") c->option_doc_sql = value;
			else if(key == "doc-sqlite3") c->option_doc_sqlite3 = value;
			else if(key == "doc-xml") c->option_doc_xml = value;
			else if(key == "doc-html") c->option_doc_html = value;
			else {
				cout << "Error: Unknown argument '" << key << "'" << endl;
				exit(1);
			}
		} else c->option_i = argv[i];
	}
	
	// set result name
	if(c->option_n == "") {
		if(c->option_i.find_last_of('.') != string::npos)
			c->option_n = c->option_i.substr(0, c->option_i.find_last_of('.'));
		else c->option_n = c->option_i;
	}
	
	// check optimsation level
	if(c->option_o != "") {
		if(c->option_o != "0" && c->option_o != "1" && c->option_o != "2" &&
		   c->option_o != "3" && c->option_o != "s") {
			cerr << "Error: Invalid optimsation level '" << c->option_o << "'" << endl;
			exit(1);
		}
	}
	
	// check Object-safety level
	if(c->option_s != 0 && c->option_s != 1 && c->option_s != 2 && c->option_s != 3) {
		cerr << "Error: Invalid Object-safe level '" << c->option_s << "'" << endl;
		exit(1);
	}
	
	// print all variables
	if(c->option_V) {
		cout << "--------------------------------------------------" << endl;
		cout << "-c="  << boolOnOff(c->option_c) << endl;
		cout << "-e="  << boolOnOff(c->option_e) << endl;
		cout << "-h="  << boolOnOff(c->option_h) << endl;
		cout << "-K="  << boolOnOff(c->option_K) << endl;
		cout << "-i='" << c->option_i << "'" << endl;
		cout << "-n='" << c->option_n << "'" << endl;
		cout << "-o='" << c->option_o << "'" << endl;
		cout << "-s='" << c->option_s << "'" << endl;
		cout << "-v="  << boolOnOff(c->option_v) << endl;
		cout << "-V="  << boolOnOff(c->option_V) << endl;
		cout << "-w='" << c->option_w << "'" << endl;
		cout << "-W='" << c->option_W << "'" << endl;
		cout << "-x="  << boolOnOff(c->option_x) << endl;
		cout << "--doc-sql='" << c->option_doc_sql << "'" << endl;
		cout << "--doc-sqlite3='" << c->option_doc_sqlite3 << "'" << endl;
		cout << "--doc-xml='" << c->option_doc_xml << "'" << endl;
		cout << "--doc-html='" << c->option_doc_html << "'" << endl;
		cout << "--------------------------------------------------" << endl;
	}
	
	// print version
	if(c->option_v) {
		cout << "maven v1.0" << endl;
		exit(0);
	}
	
	// there must be a file given
	if(c->option_i == "" && c->option_x == false)
		die("No input files");
}
