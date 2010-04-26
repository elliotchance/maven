/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "struct_MavenDocTag.h"
#include "strings.h"
#include "files.h"
#include "output.h"
#include "doc.h"

using namespace std;

void generateHTMLMethodTags(ofstream& file, MavenFunction f) {
	if(f.isPublic)
		fileWriteLine(file, "[<span class=\"keyword\">public</span>] ");
	else fileWriteLine(file, "[<span class=\"keyword\">private</span>] ");
	if(f.isConstant)
		fileWriteLine(file, "[<span class=\"keyword\">constant</span>] ");
	if(f.isStatic)
		fileWriteLine(file, "[<span class=\"keyword\">static</span>] ");
	if(f.isExternal)
		fileWriteLine(file, "[<span class=\"keyword\">external</span>] ");
	if(f.isOverride)
		fileWriteLine(file, "[override] ");
	if(f.atLine > 0)
		fileWriteLine(file, "[line " + intToString(f.atLine) + "]");
}

void generateHTMLVariableTags(ofstream& file, MavenVariable f) {
	if(f.isPublic)
		fileWriteLine(file, "[<span class=\"keyword\">public</span>] ");
	else fileWriteLine(file, "[<span class=\"keyword\">private</span>] ");
	if(f.isStatic)
		fileWriteLine(file, "[<span class=\"keyword\">static</span>] ");
	if(f.isExternal)
		fileWriteLine(file, "[<span class=\"keyword\">external</span>] ");
	if(f.atLine > 0)
		fileWriteLine(file, "[line " + intToString(f.atLine) + "]");
}

void generateHTMLHeader(ofstream& file, string extraBodyAttributes) {
	fileWriteLine(file, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
	fileWriteLine(file, "<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	fileWriteLine(file, "<head>");
	fileWriteLine(file, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />");
	fileWriteLine(file, "<title>maven documentation</title>");
	fileWriteLine(file, "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />");
	fileWriteLine(file, "<script src=\"scripts.js\"></script>");
	fileWriteLine(file, "</head>");
	fileWriteLine(file, "<body" + extraBodyAttributes + ">");
}

void generateHTMLFooter(ofstream& file) {
	fileWriteLine(file, "</body>");
	fileWriteLine(file, "</html>");
}

int countNonInheritedVariables(MavenObject* o) {
	int r = 0;
	for(int i = 0; i < o->variables->length(); ++i) {
		if(!o->variables->at(i).isInherited)
			++r;
	}
	return r;
}

int countConstructors(MavenObject* o) {
	int r = 0;
	for(int i = 0; i < o->functions->length(); ++i) {
		if(o->functions->at(i).name == o->name)
			++r;
	}
	return r;
}

int countOperatorMethods(MavenObject* o) {
	int r = 0;
	for(int i = 0; i < o->functions->length(); ++i) {
		if(o->functions->at(i).name.substr(0, 9) == "operator_")
			++r;
	}
	return r;
}

int countNonInheritedNormalMethods(MavenObject* o) {
	int r = 0;
	for(int i = 0; i < o->functions->length(); ++i) {
		if(o->functions->at(i).isInherited)
			continue;
		if(o->functions->at(i).name.substr(0, 9) == "operator_")
			continue;
		if(o->functions->at(i).name == o->name)
			continue;
		++r;
	}
	return r;
}

void generateHTMLMethodWords(ofstream& file, MavenFunction f) {
	if(f.isExternal)
		fileWriteLine(file, "external");
	if(f.isPublic)
		fileWriteLine(file, " public");
	else fileWriteLine(file, " private");
	if(f.isConstant)
		fileWriteLine(file, " constant");
	if(f.isStatic)
		fileWriteLine(file, " static");
}

string generateHTMLCommentTag(MavenCompiler* c, string input) {
	StringList lines = split('\n', input);
	string line, output = "", lastline = "";
	
	for(int i = 0; i < lines.length(); ++i) {
		line = trim(lines[i]);
		
		// process @code
		if(line == "@code") {
			++i;
			string code = "";
			for(; i < lines.length(); ++i) {
				line = trim(lines[i]);
				if(line == "@endcode")
					break;
				code += line + "\n";
			}
			++i;
			output += colourHTMLCode(c, code);
			continue;
		}
		
		if(line == "" && lastline != "" && i < lines.length() - 1)
			output += "<br />";
		else output += line + "\n";
		lastline = line;
	}
	
	// undocumented
	if(trim(output) == "")
		return "<i>Undocumented.</i>";
	
	return output;
}

void generateHTML(MavenCompiler* c) {
	// create the folder
	string docdir = combinePaths(c->currentDirectory, c->option_doc_html, true);
	cout << "Creating folder " << docdir << endl;
	makeDirectory(docdir);
	
	// perform all the sorting
	cout << "Sorting entities" << endl;
	c->namespaces->sortNamespaces();
	for(int i = 0; i < c->namespaces->length(); ++i) {
		c->namespaces->at(i).sortObjects();
		c->namespaces->at(i).sortEnums();
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			c->namespaces->at(i).objects->at(j)->variables->sortVariables();
			c->namespaces->at(i).objects->at(j)->functions->sortFunctions();
		}
	}
	
	// CSS styles
	cout << "Generating file " << docdir + "style.css" << endl;
	ofstream cssfile;
	cssfile.open((docdir + "style.css").c_str());
	string cssfile_contents = "\
	body {\n\
	font-family: Verdana, Geneva, sans-serif;\n\
	font-size: 12px;\n\
	}\n\
	.keyword {\n\
	font-family: \"Courier New\", Courier, monospace;\n\
	font-weight: bold;\n\
	color: #639;\n\
	}\n\
	.entity {\n\
	font-family: \"Courier New\", Courier, monospace;\n\
	font-size: 12px;\n\
	font-weight: bold;\n\
	color: #000;\n\
	}\n\
	.fixed {\n\
	font-family: \"Courier New\", Courier, monospace;\n\
	}\n\
	.bordertop {\n\
	border-top: solid 1px #CCC;\n\
	}\n\
	.sectionhead {\n\
	border-bottom: solid 1px #CCC;\n\
	font-size: 16px;\n\
	font-weight: bold;\n\
	background-color: #CCC;\n\
	padding: 3px;\n\
	}\n\
	.section {\n\
	border: solid 1px #CCC;\n\
	padding: 3px;\n\
	}\n\
	.sectiontight {\n\
	border: solid 1px #CCC;\n\
	}\n\
	.sectionmember {\n\
	border-bottom: solid 1px #CCC;\n\
	font-size: 16px;\n\
	margin-bottom: 5px;\n\
	font-family: Courier, monospace;\n\
	}\n";
	cssfile.write(cssfile_contents.c_str(), cssfile_contents.length());
	cssfile.close();
	
	// JavaScript
	cout << "Generating file " << docdir + "scripts.js" << endl;
	ofstream jsfile;
	jsfile.open((docdir + "scripts.js").c_str());
	string jsfile_contents = "\
	function highlightMethod(id) {\n\
	document.getElementById('methodlist' + id).bgColor = '#EEEEEE';\n\
	}\n\
	\n\
	function unhighlightMethod(id) {\n\
	document.getElementById('methodlist' + id).bgColor = '#FFFFFF';\n\
	}\n\
	";
	jsfile.write(jsfile_contents.c_str(), jsfile_contents.length());
	jsfile.close();
	
	// index page
	cout << "Generating file " << docdir + "index.html" << endl;
	ofstream mainfile;
	mainfile.open((docdir + "index.html").c_str());
	generateHTMLHeader(mainfile);
	fileWriteLine(mainfile, "<frameset cols=\"200,*\" frameborder=\"1\" border=\"1\" framespacing=\"0\">");
	fileWriteLine(mainfile, "<frame src=\"classes.html\" name=\"leftFrame\" scrolling=\"Yes\" id=\"leftFrame\" title=\"leftFrame\" />");
	fileWriteLine(mainfile, "<frame src=\"classes2.html\" name=\"mainFrame\" scrolling=\"Yes\" id=\"mainFrame\" title=\"mainFrame\" />");
	fileWriteLine(mainfile, "</frameset>");
	generateHTMLFooter(mainfile);
	mainfile.close();
	
	// classes list
	cout << "Generating file " << docdir + "classes.html" << endl;
	ofstream classesfile;
	classesfile.open((docdir + "classes.html").c_str());
	generateHTMLHeader(classesfile, " style=\"padding: 0px; margin: 0px\"");
	fileWriteLine(classesfile, "<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\">");
	fileWriteLine(classesfile, "<tr>");
	fileWriteLine(classesfile, "<td bgcolor=\"#CCCCCC\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(classesfile, "<a href=\"classes.html\" style=\"text-decoration: none; color: #0000FF\">Classes</a></td>");
	fileWriteLine(classesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(classesfile, "<a href=\"namespaces.html\" style=\"text-decoration: none; color: #0000FF\">Namespaces</a></td>");
	fileWriteLine(classesfile, "</tr>");
	fileWriteLine(classesfile, "<tr>");
	fileWriteLine(classesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(classesfile, "<a href=\"files.html\" style=\"text-decoration: none; color: #0000FF\">Files</a></td>");
	fileWriteLine(classesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(classesfile, "<a href=\"fullindex.html\" style=\"text-decoration: none; color: #0000FF\">Index</a></td>");
	fileWriteLine(classesfile, "</tr>");
	fileWriteLine(classesfile, "</table><div style=\"padding: 5px\">");
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			fileWriteLine(classesfile, "<a href=\"class_" + c->namespaces->at(i).name + "_" +
						  c->namespaces->at(i).objects->at(j)->name + ".html\" target=\"mainFrame\">" +
						  c->namespaces->at(i).name + "." + c->namespaces->at(i).objects->at(j)->name + "</a><br />");
		}
	}
	fileWriteLine(classesfile, "</div>");
	generateHTMLFooter(classesfile);
	classesfile.close();
	
	// classes list
	cout << "Generating file " << docdir + "classes2.html" << endl;
	ofstream classes2file;
	classes2file.open((docdir + "classes2.html").c_str());
	generateHTMLHeader(classes2file);
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			fileWriteLine(classes2file, "<a href=\"class_" + c->namespaces->at(i).name + "_" +
						  c->namespaces->at(i).objects->at(j)->name + ".html\" target=\"mainFrame\">" +
						  c->namespaces->at(i).name + "." + c->namespaces->at(i).objects->at(j)->name + "</a><br />");
			fileWriteLine(classes2file, c->namespaces->at(i).objects->at(j)->doc.tagBrief + "<br />");
		}
	}
	generateHTMLFooter(classes2file);
	classes2file.close();
	
	// colour code files
	for(int i = 0; i < c->filesParsed.length(); ++i) {
		string outputname = basename(c->filesParsed[i]);
		cout << "Generating file " << docdir + "file_" << outputname << ".html" << endl;
		ofstream outputfile;
		outputfile.open((docdir + "file_" + outputname + ".html").c_str());
		generateHTMLHeader(outputfile);
		
		// open the read file
		ifstream infile;
		infile.open(c->filesParsed[i].c_str());
		if(infile.is_open()) {
			
			// read whole file
			string wholeFile = "";
			while(!infile.eof())
				wholeFile += infile.get();
			infile.close();
			
			// format and output
			fileWriteLine(outputfile, colourHTMLCode(c, wholeFile.substr(0, wholeFile.length() - 1)));
		}
		
		generateHTMLFooter(outputfile);
		outputfile.close();
	}
	
	// namespaces list
	cout << "Generating file " << docdir + "namespaces.html" << endl;
	ofstream namespacesfile;
	namespacesfile.open((docdir + "namespaces.html").c_str());
	generateHTMLHeader(namespacesfile, " style=\"padding: 0px; margin: 0px\"");
	fileWriteLine(namespacesfile, "<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\">");
	fileWriteLine(namespacesfile, "<tr>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(namespacesfile, "<a href=\"classes.html\" style=\"text-decoration: none; color: #0000FF\">Classes</a></td>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#CCCCCC\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(namespacesfile, "<a href=\"namespaces.html\" style=\"text-decoration: none; color: #0000FF\">Namespaces</a></td>");
	fileWriteLine(namespacesfile, "</tr>");
	fileWriteLine(namespacesfile, "<tr>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(namespacesfile, "<a href=\"files.html\" style=\"text-decoration: none; color: #0000FF\">Files</a></td>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(namespacesfile, "<a href=\"fullindex.html\" style=\"text-decoration: none; color: #0000FF\">Index</a></td>");
	fileWriteLine(namespacesfile, "</tr>");
	fileWriteLine(namespacesfile, "</table><div style=\"padding: 5px\">");
	for(int i = 0; i < c->namespaces->length(); ++i) {
		fileWriteLine(namespacesfile, "<a href=\"namespace_" + c->namespaces->at(i).name +
					  ".html\" target=\"mainFrame\">" + c->namespaces->at(i).name + "</a><br />");
	}
	fileWriteLine(namespacesfile, "</div>");
	generateHTMLFooter(namespacesfile);
	namespacesfile.close();
	
	// file list
	cout << "Generating file " << docdir + "files.html" << endl;
	ofstream filesfile;
	filesfile.open((docdir + "files.html").c_str());
	generateHTMLHeader(filesfile, " style=\"padding: 0px; margin: 0px\"");
	fileWriteLine(filesfile, "<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\">");
	fileWriteLine(filesfile, "<tr>");
	fileWriteLine(filesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(filesfile, "<a href=\"classes.html\" style=\"text-decoration: none; color: #0000FF\">Classes</a></td>");
	fileWriteLine(filesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(filesfile, "<a href=\"namespaces.html\" style=\"text-decoration: none; color: #0000FF\">Namespaces</a></td>");
	fileWriteLine(filesfile, "</tr>");
	fileWriteLine(filesfile, "<tr>");
	fileWriteLine(filesfile, "<td bgcolor=\"#CCCCCC\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC; border-right: solid 1px #CCCCCC\">");
	fileWriteLine(filesfile, "<a href=\"files.html\" style=\"text-decoration: none; color: #0000FF\">Files</a></td>");
	fileWriteLine(filesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\" style=\"border-bottom: solid 1px #CCCCCC\">");
	fileWriteLine(filesfile, "<a href=\"fullindex.html\" style=\"text-decoration: none; color: #0000FF\">Index</a></td>");
	fileWriteLine(filesfile, "</tr>");
	fileWriteLine(filesfile, "</table><div style=\"padding: 5px\">");
	for(int i = 0; i < c->filesParsed.length(); ++i) {
		fileWriteLine(filesfile, "<a href=\"file_" + basename(c->filesParsed[i]) +
					  ".html\" target=\"mainFrame\">" + basename(c->filesParsed[i]) + "</a><br />");
	}
	fileWriteLine(filesfile, "</div>");
	generateHTMLFooter(filesfile);
	filesfile.close();
	
	// classes
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			// create file
			string outputfile = docdir + "class_" + c->namespaces->at(i).name + "_" + 
			c->namespaces->at(i).objects->at(j)->name + ".html";
			cout << "Generating file " << outputfile << endl;
			ofstream file;
			file.open(outputfile.c_str());
			generateHTMLHeader(file);
			
			fileWriteLine(file, "<h1>Class: <span class=\"fixed\">");
			fileWriteLine(file, "<a href=\"namespace_" + c->namespaces->at(i).name +
						  ".html\" target=\"mainFrame\">" + c->namespaces->at(i).name +
						  "</a>.<a href=\"class_" + c->namespaces->at(i).name + "_" +
						  c->namespaces->at(i).objects->at(j)->name + ".html\">" +
						  c->namespaces->at(i).objects->at(j)->name + "</a></span></h1>");
			
			// inheritance
			if(c->namespaces->at(i).objects->at(j)->extends != "")
				fileWriteLine(file, "<h3>Inherits from: <span class=\"fixed\"><a href=\"#\">" +
							  c->namespaces->at(i).objects->at(j)->extends + "</a></span></h3>");
			
			// contents
			fileWriteLine(file, "<div class=\"sectionhead\">Contents</div>");
			fileWriteLine(file, "<div class=\"section\"><ul style=\"margin-top: 0px; margin-bottom: 0px; padding-left: 25px\">");
			if(c->namespaces->at(i).objects->at(j)->doc.inUse())
				fileWriteLine(file, "<li><a href=\"#Description\" style=\"color: #0000CC\">Description</a></li>");
			if(countNonInheritedVariables(c->namespaces->at(i).objects->at(j)) > 0)
				fileWriteLine(file, "<li><a href=\"#MemberVariables\" style=\"color: #0000CC\">Member Variables</a></li>");
			if(countConstructors(c->namespaces->at(i).objects->at(j)) > 0)
				fileWriteLine(file, "<li><a href=\"#Constructors\" style=\"color: #0000CC\">Constructors</a></li>");
			if(countNonInheritedNormalMethods(c->namespaces->at(i).objects->at(j)) > 0)
				fileWriteLine(file, "<li><a href=\"#MemberMethods\" style=\"color: #0000CC\">Member Methods</a></li>");
			if(countOperatorMethods(c->namespaces->at(i).objects->at(j)) > 0)
				fileWriteLine(file, "<li><a href=\"#OperatorMethods\" style=\"color: #0000CC\">Operator Methods</a></li>");
			fileWriteLine(file, "</ul></div><br /><br />");
			
			// class description
			if(c->namespaces->at(i).objects->at(j)->doc.inUse()) {
				fileWriteLine(file, "<div class=\"sectionhead\"><a name=\"Description\" />Description</div>");
				fileWriteLine(file, "<div class=\"section\">");
				if(c->namespaces->at(i).objects->at(j)->doc.tagBrief != "")
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->doc.tagBrief + "<br />");
				fileWriteLine(file, c->namespaces->at(i).objects->at(j)->doc.body);
				fileWriteLine(file, "</div><br />");
			}
			
			// variables contents
			if(countNonInheritedVariables(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"sectionhead\"><a name=\"MemberVariables\" />Member Variables</div>");
				fileWriteLine(file, "<div class=\"sectiontight\">");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isInherited)
						continue;
					
					fileWriteLine(file, "<tr onmouseover=\"highlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() +
								  "')\" onmouseout=\"unhighlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() +
								  "')\" id=\"methodlist" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() + "\">");
					
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" class=\"bordertop\" style=\"white-space: nowrap\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isExternal)
						fileWriteLine(file, "external");
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isPublic)
						fileWriteLine(file, " public");
					else fileWriteLine(file, " private");
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isStatic)
						fileWriteLine(file, " static");
					
					fileWriteLine(file, "&nbsp;</span></td>");
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\">" + c->namespaces->at(i).objects->at(j)->variables->at(k).type);
					fileWriteLine(file, " <span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).name + "</a>");
					fileWriteLine(file, "</span></span>");
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).doc.tagBrief != "")
						fileWriteLine(file, "<br />" + c->namespaces->at(i).objects->at(j)->variables->at(k).doc.tagBrief);
					fileWriteLine(file, "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div><br />");
			}
			
			// constructors contents
			if(countConstructors(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"sectionhead\"><a name=\"Constructors\" />Constructors</div>");
				fileWriteLine(file, "<div class=\"sectiontight\">");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).name != c->namespaces->at(i).objects->at(j)->name)
						continue;
					
					fileWriteLine(file, "<tr onmouseover=\"highlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" onmouseout=\"unhighlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" id=\"methodlist" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">");
					
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" class=\"bordertop\" style=\"white-space: nowrap\" class=\"borderbottom\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\" class=\"borderbottom\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagBrief + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div><br />");
			}
			
			// functions contents
			if(countNonInheritedNormalMethods(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"sectionhead\"><a name=\"MemberMethods\" />Member Methods</div>");
				fileWriteLine(file, "<div class=\"sectiontight\">");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).name.substr(0, 9) == "operator_")
						continue;
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).isInherited)
						continue;
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).name == c->namespaces->at(i).objects->at(j)->name)
						continue;
					
					fileWriteLine(file, "<tr onmouseover=\"highlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" onmouseout=\"unhighlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" id=\"methodlist" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">");
					
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" class=\"bordertop\" style=\"white-space: nowrap\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagBrief + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div><br />");
			}
			
			// operator methods contents
			if(countOperatorMethods(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"sectionhead\"><a name=\"OperatorMethods\" />Operator Methods</div>");
				fileWriteLine(file, "<div class=\"sectiontight\">");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0, count = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).name.substr(0, 9) != "operator_")
						continue;
					
					fileWriteLine(file, "<tr onmouseover=\"highlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" onmouseout=\"unhighlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" id=\"methodlist" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">");
					
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" class=\"bordertop\" style=\"white-space: nowrap\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagBrief + "</td>");
					fileWriteLine(file, "</tr>");
					++count;
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div><br />");
			}
			
			// variables description
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
				if(!c->namespaces->at(i).objects->at(j)->variables->at(k).isInherited) {
					fileWriteLine(file, string("<a name=\"") +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() + "\" />");
					fileWriteLine(file, "<div class=\"section\">");
					fileWriteLine(file, "<div class=\"sectionmember\">");
					fileWriteLine(file, "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tr>");
					fileWriteLine(file, "<td>" + c->namespaces->at(i).objects->at(j)->variables->at(k).type + " <strong>" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).name + "</strong></td>");
					fileWriteLine(file, "<td align=\"right\" style=\"font-size: 12px\"><strong>");
					generateHTMLVariableTags(file, c->namespaces->at(i).objects->at(j)->variables->at(k));
					fileWriteLine(file, "</strong></td></tr></table>");
					fileWriteLine(file, "</div>");
					fileWriteLine(file, generateHTMLCommentTag(c, c->namespaces->at(i).objects->at(j)->variables->at(k).doc.body));
					
					fileWriteLine(file, "</div><br />");
				}
			}
			
			// functions description
			for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
				if(!c->namespaces->at(i).objects->at(j)->functions->at(k).isInherited) {
					fileWriteLine(file, string("<a name=\"") +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\" />");
					fileWriteLine(file, "<div class=\"section\">");
					fileWriteLine(file, "<div class=\"sectionmember\">");
					fileWriteLine(file, "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tr>");
					fileWriteLine(file, "<td><strong>" + c->namespaces->at(i).objects->at(j)->functions->at(k).name +
								  "</strong>(" + c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() + ")</td>");
					fileWriteLine(file, "<td align=\"right\" style=\"font-size: 12px\"><strong>");
					generateHTMLMethodTags(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "</strong></td></tr></table>");
					fileWriteLine(file, "</div>");
					fileWriteLine(file, generateHTMLCommentTag(c, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body));
					
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagParam.length() > 0) {
						fileWriteLine(file, string("<br /><b>Parameters</b>"));
						for(int l = 0; l < c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagParam.length(); ++l) {
							fileWriteLine(file, string("<br />") +
										  c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagParam[l]);
						}
					}
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagReturn != "")
						fileWriteLine(file, string("<br /><b>Return: </b>") +
									  c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagReturn);
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagSince != "")
						fileWriteLine(file, string("<br /><b>Since: </b>") +
									  c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagSince);
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagThrows.length() > 0) {
						fileWriteLine(file, string("<br /><b>Throws: </b>"));
						for(int l = 0; l < c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagThrows.length(); ++l) {
							fileWriteLine(file, string("<br />") +
										  c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagThrows[l]);
						}
					}
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagVersion != "")
						fileWriteLine(file, string("<br /><b>Version: </b>") +
									  c->namespaces->at(i).objects->at(j)->functions->at(k).doc.tagVersion);
					
					fileWriteLine(file, "</div><br />");
				}
			}
			
			// clean up
			generateHTMLFooter(file);
			file.close();
		}
	}
}
