/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "struct_MavenObject.h"
#include "strings.h"
#include "files.h"
#include "output.h"

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

void generateHTMLHeader(ofstream& file) {
	fileWriteLine(file, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
	fileWriteLine(file, "<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	fileWriteLine(file, "<head>");
	fileWriteLine(file, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />");
	fileWriteLine(file, "<title>maven documentation</title>");
	fileWriteLine(file, "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />");
	fileWriteLine(file, "<script src=\"scripts.js\"></script>");
	fileWriteLine(file, "</head>");
	fileWriteLine(file, "<body>");
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

void generateHTML(MavenCompiler* c) {
	// create the folder
	string docdir = combinePaths(c->currentDirectory, c->option_doc_html, true);
	cout << "Creating folder " << docdir << endl;
	makeDirectory(docdir);
	
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
	border-top: solid 1px #999;\n\
	}\n\
	.section {\n\
	margin-bottom: 10px;\n\
	padding-bottom: 10px;\n\
	}\n\
	.sectionhead {\n\
	border-bottom: solid 1px #069;\n\
	font-size: 16px;\n\
	font-weight: bold;\n\
	margin-bottom: 5px;\n\
	}\n\
	.sectionhead2 {\n\
	font-size: 16px;\n\
	font-weight: bold;\n\
	margin-bottom: 5px;\n\
	}\n\
	.sectionmember {\n\
	border-bottom: solid 1px #069;\n\
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
	fileWriteLine(mainfile, "<frameset cols=\"200,*\" frameborder=\"yes\" border=\"1\" framespacing=\"0\">");
	fileWriteLine(mainfile, "<frame src=\"classes.html\" name=\"leftFrame\" scrolling=\"Yes\" id=\"leftFrame\" title=\"leftFrame\" />");
	fileWriteLine(mainfile, "<frame src=\"classes2.html\" name=\"mainFrame\" scrolling=\"Yes\" id=\"mainFrame\" title=\"mainFrame\" />");
	fileWriteLine(mainfile, "</frameset>");
	generateHTMLFooter(mainfile);
	mainfile.close();
	
	// classes list
	cout << "Generating file " << docdir + "classes.html" << endl;
	ofstream classesfile;
	classesfile.open((docdir + "classes.html").c_str());
	generateHTMLHeader(classesfile);
	fileWriteLine(classesfile, "<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tr>");
	fileWriteLine(classesfile, "<td bgcolor=\"#CCCCCC\" width=\"50%\" align=\"center\"><a href=\"classes.html\">Classes</a></td>");
	fileWriteLine(classesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\"><a href=\"namespaces.html\">Namespaces</a></td>");
	fileWriteLine(classesfile, "</tr></table>");
	for(int i = 0; i < c->namespaces->length(); ++i) {
		for(int j = 0; j < c->namespaces->at(i).objects->length(); ++j) {
			fileWriteLine(classesfile, "<a href=\"class_" + c->namespaces->at(i).name + "_" +
						  c->namespaces->at(i).objects->at(j)->name + ".html\" target=\"mainFrame\">" +
						  c->namespaces->at(i).name + "." + c->namespaces->at(i).objects->at(j)->name + "</a><br />");
		}
	}
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
			fileWriteLine(classes2file, "Description here<br />");
		}
	}
	generateHTMLFooter(classes2file);
	classes2file.close();
	
	// namespaces list
	cout << "Generating file " << docdir + "namespaces.html" << endl;
	ofstream namespacesfile;
	namespacesfile.open((docdir + "namespaces.html").c_str());
	generateHTMLHeader(namespacesfile);
	fileWriteLine(namespacesfile, "<table cellpadding=\"3\" cellspacing=\"0\" border=\"0\" width=\"100%\"><tr>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#EEEEEE\" width=\"50%\" align=\"center\"><a href=\"classes.html\">Classes</a></td>");
	fileWriteLine(namespacesfile, "<td bgcolor=\"#CCCCCC\" width=\"50%\" align=\"center\"><a href=\"namespaces.html\">Namespaces</a></td>");
	fileWriteLine(namespacesfile, "</tr></table>");
	for(int i = 0; i < c->namespaces->length(); ++i) {
		fileWriteLine(namespacesfile, "<a href=\"namespace_" + c->namespaces->at(i).name +
					  ".html\" target=\"mainFrame\">" + c->namespaces->at(i).name + "</a><br />");
	}
	generateHTMLFooter(classesfile);
	namespacesfile.close();
	
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
				fileWriteLine(file, "<h1>Inherits from: <span class=\"fixed\"><a href=\"#\">" +
							  c->namespaces->at(i).objects->at(j)->extends + "</a></span></h1>");
			
			// class description
			// FIXME: need a better way to check if MavenDocTag is in use
			if(trim(c->namespaces->at(i).objects->at(j)->doc.body) != "") {
				fileWriteLine(file, "<div class=\"section\">");
				fileWriteLine(file, "<div class=\"sectionhead\">Description</div>");
				fileWriteLine(file, c->namespaces->at(i).objects->at(j)->doc.body + "<br />");
				fileWriteLine(file, "</div>");
			}
			
			// variables contents
			if(countNonInheritedVariables(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"section\">");
				fileWriteLine(file, "<div class=\"sectionhead2\">Member Variables</div>");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->variables->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isInherited)
						continue;
					
					fileWriteLine(file, "<tr>");
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" style=\"white-space: nowrap\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isExternal)
						fileWriteLine(file, "external");
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isPublic)
						fileWriteLine(file, " public");
					else fileWriteLine(file, " private");
					if(c->namespaces->at(i).objects->at(j)->variables->at(k).isStatic)
						fileWriteLine(file, " static");
					
					fileWriteLine(file, "&nbsp;</span></td>");
					fileWriteLine(file, "<td class=\"fixed bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\">" + c->namespaces->at(i).objects->at(j)->variables->at(k).type);
					fileWriteLine(file, " <span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->variables->at(k).name + "</a>");
					fileWriteLine(file, "</span></span></td>");
					fileWriteLine(file, "</tr>");
					fileWriteLine(file, "<tr>");
					fileWriteLine(file, "<td nowrap=\"nowrap\">&nbsp;</td>");
					fileWriteLine(file, "<td>" + c->namespaces->at(i).objects->at(j)->variables->at(k).doc.body + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div>");
			}
			
			// constructors contents
			if(countConstructors(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"section\">");
				fileWriteLine(file, "<div class=\"sectionhead2\">Constructors</div>");
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
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" style=\"white-space: nowrap\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div>");
			}
			
			// functions contents
			if(c->namespaces->at(i).objects->at(j)->functions->length() > 0) {
				fileWriteLine(file, "<div class=\"section\">");
				fileWriteLine(file, "<div class=\"sectionhead2\">Member Methods</div>");
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
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" style=\"white-space: nowrap\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div>");
			}
			
			// operator methods contents
			if(countOperatorMethods(c->namespaces->at(i).objects->at(j)) > 0) {
				fileWriteLine(file, "<div class=\"section\">");
				fileWriteLine(file, "<div class=\"sectionhead2\">Operators</div>");
				fileWriteLine(file, "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\">");
				
				for(int k = 0; k < c->namespaces->at(i).objects->at(j)->functions->length(); ++k) {
					if(c->namespaces->at(i).objects->at(j)->functions->at(k).name.substr(0, 9) != "operator_")
						continue;
					
					fileWriteLine(file, "<tr onmouseover=\"highlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" onmouseout=\"unhighlightMethod('" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() +
								  "')\" id=\"methodlist" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">");
					fileWriteLine(file, "<td valign=\"top\" width=\"10\" style=\"white-space: nowrap\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"keyword\">");
					generateHTMLMethodWords(file, c->namespaces->at(i).objects->at(j)->functions->at(k));
					fileWriteLine(file, "&nbsp;</span></td>");
					
					fileWriteLine(file, "<td valign=\"top\" class=\"bordertop\">");
					fileWriteLine(file, "<span class=\"fixed\"><span class=\"entity\"><a href=\"#" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getAnchorID() + "\">" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).name + "</a></span>(" +
								  c->namespaces->at(i).objects->at(j)->functions->at(k).getSignature() +
								  ")</span><br />");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body + "</td>");
					fileWriteLine(file, "</tr>");
				}
				
				fileWriteLine(file, "</table>");
				fileWriteLine(file, "</div>");
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
					fileWriteLine(file, "<td align=\"right\" style=\"font-size: 12px\">");
					generateHTMLVariableTags(file, c->namespaces->at(i).objects->at(j)->variables->at(k));
					fileWriteLine(file, "</strong></td></tr></table>");
					fileWriteLine(file, "</div>");
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->variables->at(k).doc.body);
					
					fileWriteLine(file, "</div>");
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
					fileWriteLine(file, c->namespaces->at(i).objects->at(j)->functions->at(k).doc.body);
					
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
					
					fileWriteLine(file, "</div>");
				}
			}
			
			// clean up
			generateHTMLFooter(file);
			file.close();
			
			/*
			 
			 string arguments = "";
			 for(int l = 0; l < c->namespaces->at(i).objects->at(j)->functions->at(k).args.length(); ++l) {
			 if(l) arguments += ", ";
			 arguments += c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].type + " "
			 + c->namespaces->at(i).objects->at(j)->functions->at(k).args[l].name;
			 }
			 sql << sqlSafe(arguments)
			 }*/
		}
	}
}
