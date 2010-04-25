/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"
#include "struct_MavenCompiler.h"
#include "output.h"

void writeEntryPoint(MavenCompiler* c) {
	// this is to close the namespace
	writeCPPLine(c, "}\n");
	
	// the only purpose of this function to create main()
	// from the bits of scattered code collected along the way
	// as well as the global variables.
	writeCPPLine(c, "int main(int argc, mbyte** argv) {");
	
	// here we setup Application
	writeCPPLine(c, "maven::Application$static::program = new maven::String(argv[0]);");
	writeCPPLine(c, "maven::Application$static::arguments = new maven::objectArray((long) argc - 1);");
	writeCPPLine(c, "for(int argcount = 1; argcount < argc; ++argcount)");
	writeCPPLine(c, "maven::Application$static::arguments->a[argcount - 1] = (maven::Object*) new maven::String(argv[argcount]);");
	
	// the core bits
	for(int i = 0; i < c->entryPoint.length(); ++i)
		c->cppFileHandle << c->entryPoint[i] << endl;
	
	// global object safety checking
	writeCPPLine(c, "} catch(maven::Exception* caughtGlobalException) {");
	writeCPPLine(c, "  std::cout << caughtGlobalException->description()->s;");
	writeCPPLine(c, "  exit(1);");
	writeCPPLine(c, "}");
	writeCPPLine(c, "return 0;");
	
	writeCPPLine(c, "}\n");
	
	// now we do the post lines
	for(int i = 0; i < c->postLines.size(); ++i)
		writeCPPLine(c, c->postLines[i]);
}
