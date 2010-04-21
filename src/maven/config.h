/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_CONFIG_H
#define _MAVEN_CONFIG_H 1

/**
 * The operating system, can be
 * <pre>
 * 1 - UNIX
 * 2 - WINDOWS
 * </pre>
 */
#define MAVEN_OS


// choose operating system
#ifdef _WIN32
	#undef MAVEN_OS
	#define MAVEN_OS 2
#elif __GNUC__
	#undef MAVEN_OS
	#define MAVEN_OS 1
#endif


// system commands
#if MAVEN_OS == 1

	#define SYSTEM_RM "rm -f "
	#define SYSTEM_CP "cp -f "
	#define SYSTEM_MKDIR "mkdir "

#elif MAVEN_OS == 2

	#define SYSTEM_RM "del -f "
	#define SYSTEM_CP "copy -y "
	#define SYSTEM_MKDIR "mkdir "

#endif

#endif
