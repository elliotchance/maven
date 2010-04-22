/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "strings.h"
#include "files.h"

MavenVariable getCompilerVariable(MavenCompiler* c, string name) {
	MavenVariable v;
	v.name = name;
	
	// for time variables
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	if(name == "@Class") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + c->currentClass + "\")";
		return v;
	}
	if(name == "@CompilerVersion") {
		v.type = "int";
		v.defaultValue = intToString(MAVEN_COMPILER_VERSION);
		return v;
	}
	if(name == "@CompilerName") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + string(MAVEN_COMPILER_NAME) + "\")";
		return v;
	}
	if(name == "@DateD") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(timeinfo->tm_mday) + "\")";
		return v;
	}
	if(name == "@DateDD") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_mday, 2) + "\")";
		return v;
	}
	if(name == "@DateM") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(timeinfo->tm_mon) + "\")";
		return v;
	}
	if(name == "@DateMM") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_mon, 2) + "\")";
		return v;
	}
	if(name == "@DateYY") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_year - 100, 2) + "\")";
		return v;
	}
	if(name == "@DateYYYY") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_year + 1900, 2) + "\")";
		return v;
	}
	if(name == "@File") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + basename(c->currentFile) + "\")";
		return v;
	}
	if(name == "@FilePath") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + combinePaths(c->currentDirectory, c->currentFile, false) + "\")";
		return v;
	}
	if(name == "@Function") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + c->currentFunction + "\")";
		return v;
	}
	if(name == "@Line") {
		v.type = "int";
		v.defaultValue = intToString(c->lineNumber);
		return v;
	}
	if(name == "@Namespace") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + c->currentNamespace + "\")";
		return v;
	}
	if(name == "@Now") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(1900 + timeinfo->tm_year) + "-" +
		padIntToString(timeinfo->tm_mon, 2) + "-" + padIntToString(timeinfo->tm_mday, 2) + " " +
		padIntToString(timeinfo->tm_hour, 2) + ":" + padIntToString(timeinfo->tm_min, 2) + ":" +
		padIntToString(timeinfo->tm_sec, 2) + "\")";
		return v;
	}
	if(name == "@TimeH") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(timeinfo->tm_hour) + "\")";
		return v;
	}
	if(name == "@TimeHH") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_hour, 2) + "\")";
		return v;
	}
	if(name == "@TimeM") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(timeinfo->tm_min) + "\")";
		return v;
	}
	if(name == "@TimeMM") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_min, 2) + "\")";
		return v;
	}
	if(name == "@TimeS") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(timeinfo->tm_sec) + "\")";
		return v;
	}
	if(name == "@TimeSS") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + padIntToString(timeinfo->tm_sec, 2) + "\")";
		return v;
	}
	if(name == "@Today") {
		v.type = "maven.String";
		v.defaultValue = "new maven::String(\"" + intToString(1900 + timeinfo->tm_year) + "-" +
		padIntToString(timeinfo->tm_mon, 2) + "-" + padIntToString(timeinfo->tm_mday, 2) + "\")";
		return v;
	}
	
	v.name = MAVEN_INVALID;
	return v;
}
