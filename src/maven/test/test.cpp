/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "../test.h"

#include <dirent.h>

void getRecursiveFiles(vector<string> &stack, string path) {
	DIR *pDIR;
	struct dirent *entry;
	
	if(pDIR = opendir(path.c_str())){
		while(entry = readdir(pDIR)){
			if(entry->d_name[0] == '.')
				continue;
			if(entry->d_type == DT_DIR)
				getRecursiveFiles(stack, path + "/" + entry->d_name);
			else stack.push_back(path + "/" + entry->d_name);
		}
		closedir(pDIR);
	}
}

int runTests() {
	string testDirectory = "../../test/";
	
	cout << "Preparing... ";
	vector<string> files;
	getRecursiveFiles(files, testDirectory + "test");
	cout << "Done" << endl;
	
	cout << "Running..." << endl;
	string cmd;
	
	for(int i = 0; i < files.size(); ++i) {
		if(files[i].substr(files[i].length() - 4) == ".mav") {
			// compile
			cmd = "./maven \"";
			cmd += files[i] + "\"";
			cout << files[i] << "... ";
			system(cmd.c_str());
			
			// run and capture output
			cmd = "\"" + files[i].substr(0, files[i].length() - 4) + "\"";
			FILE *output = popen(cmd.c_str(), "r");
			if(!output) {
				cout << "Could not open pipe for " << cmd << endl;
				exit(1);
			}
			
			char buffer[1024];
			char *line_p = fgets(buffer, sizeof(buffer), output);
			pclose(output);
			
			if(line_p == NULL) {
				cout << "Output is NULL" << endl;
				continue;
			}
			
			// get the confirmed result to compare to
			string confirm = testDirectory + "result" + files[i].substr(testDirectory.length() + 4);
			confirm = confirm.substr(0, confirm.find_last_of(".")) + ".txt";
			ifstream expectedResult;
			expectedResult.open(confirm.c_str());
			if(!expectedResult.is_open()) {
				cout << "Could not open file " << confirm << endl;
				exit(1);
			}
			
			// check result
			string wholeFile = "";
			while(!expectedResult.eof())
				wholeFile += expectedResult.get();
			expectedResult.close();
			
			if(wholeFile.substr(0, wholeFile.length() - 1) == line_p)
				cout << "PASS" << endl;
			else {
				cout << "FAIL" << endl;
				cout << "'" << wholeFile << "' != '" << line_p << "'" << endl;
			}
			
			// clean up
			system((string(SYSTEM_RM) + " \"" + confirm.substr(0, confirm.find_last_of(".")) + "\"").c_str());
		}
	}
	cout << "All Done" << endl;
	
	return 0;
}
