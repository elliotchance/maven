/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_COMPILER_H
#define _MAVEN_STRUCT_COMPILER_H 1

#include "maven.h"
#include "enum_MavenBrackets.h"
#include "struct_StringList.h"
#include "struct_MavenErrors.h"
#include "struct_MavenVariables.h"
#include "struct_MavenObjectDiscovery.h"
#include "struct_MavenPair.h"
#include "struct_MavenINI.h"
#include "struct_MavenNamespaces.h"

struct MavenCompiler {
	
	/**
	 * @brief Map file handle for generated .mmap
	 */
	ofstream mapFileHandle;
	
	/**
	 * @brief C++ file generated by the maven compiler.
	 */
	ofstream cppFileHandle;
	
	/**
	 * @brief Holds all object and variable information for all namespaces.
	 */
	MavenNamespaces* namespaces;
	
	/**
	 * @brief Stack for errors.
	 */
	MavenErrors errors;
	
	/**
	 * @brief Current line number.
	 */
	int lineNumber;
	
	/**
	 * @brief Lines to be prepended when creating the main() function.
	 */
	StringList entryPoint;
	
	/**
	 * @brief Current maven file being processed.
	 */
	string currentFile;
	
	/**
	 * @brief Current active namespace.
	 */
	string currentNamespace;
	
	/**
	 * @brief Current active class name (bare name).
	 */
	string currentClass;
	
	/**
	 * @brief Current function.
	 */
	string currentFunction;
	
	int currentBlockDepth;
	
	int dissectDepth;
	
	StringList reservedWords;
	
	vector<MavenVariables> localScope;
	
	StringList* imports;
	
	string doc;
	
	vector<MavenBrackets> bracketStack;
	
	vector<MavenObjectDiscovery> discovery;
	
	/**
	 * @brief The total number of lines parsed.
	 */
	int totalLines;
	
	/**
	 * @brief The total number of files parsed.
	 */
	int totalFiles;
	
	long start;
	
	/**
	 * @brief Objects to check for ObjectNilException and BoundsException.
	 */
	vector<MavenPair> objectCheck;
	
	vector<string> postLines;
	
	vector<string> selectors;
	
	/**
	 * @brief This is collected throughout the dissection of the line then prepended before flushing
	 *        to the CPP file.
	 */
	string beforeLine;
	
	/**
	 * @brief The current directory is where maven is executed from, not where maven is located.
	 */
	string currentDirectory;
	
	/**
	 * @brief The location of the bin/ directory that the maven executable resides in.
	 */
	string binDirectory;
	
	/**
	 * @brief Filled with maven.ini before each maven compile.
	 */
	MavenINI iniFile;
	
	/**
	 * @brief All the extra .o's to include in the compilation.
	 */
	StringList extraLibraries;
	
	/**
	 * @brief Set and reset with switch().
	 */
	string switchArgument;
	
	/**
	 * @brief The UID is a unique ID for naming temporary objects.
	 */
	int UID;
	
	/**
	 * @brief For use with the 'with' statement.
	 */
	MavenVariable withObject;
	
	/**
	 * @brief The last statements, important for 'if' and 'do'.
	 */
	string lastStatament;
	
public:
	
	/**
	 * @brief Compile object file but do not link.
	 */
	bool option_c;
	
	/**
	 * @brief Execute after compilation.
	 */
	bool option_e;
	
	/**
	 * @brief Show help and quit.
	 */
	bool option_h;
	
	/**
	 * @brief Input file(s)
	 */
	string option_i;
	
	/**
	 * @brief Keep CPP and MMAP
	 */
	bool option_K;
	
	/**
	 * @brief Result executable/object name.
	 */
	string option_n;
	
	/**
	 * @brief Optimisation level (GNU specific.)
	 */
	string option_o;
	
	/**
	 * @brief Show compilation statistics.
	 */
	bool option_r;
	
	/**
	 * @brief Object-safe level.
	 */
	int option_s;
	
	/**
	 * @brief Print version and quit.
	 */
	bool option_v;
	
	/**
	 * @brief Show all compiler variables before compiling.
	 */
	bool option_V;
	
	/**
	 * @brief Supress specific warning.
	 */
	string option_w;
	
	/**
	 * @brief Show specific warning.
	 */
	string option_W;
	
	/**
	 * @brief Do not compile or link (no input file required.)
	 */
	bool option_x;
	
	/**
	 * @brief Place for SQL documentation.
	 */
	string option_doc_sql;
	
	/**
	 * @brief Place for SQLite3 documentation.
	 */
	string option_doc_sqlite3;
	
	/**
	 * @brief Place for XML documentation.
	 */
	string option_doc_xml;
	
	/**
	 * @brief Place for HTML documentation.
	 */
	string option_doc_html;
	
	/**
	 * @brief Where maven was originally executed from.
	 */
	string option_base_path;
	
	MavenCompiler();
	
};

#endif
