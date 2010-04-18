/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

/**
 * The operating system, can be
 * <pre>
 * 1 - UNIX
 * 2 - WINDOWS
 * </pre>
 */

#ifdef _WIN32

#define MAVEN_OS 2

#elif __GNUC__

#define MAVEN_OS 1

#endif

#define MAVEN_INI_LOCATION "../../etc/maven.ini"

#if MAVEN_OS == 1

#define SYSTEM_RM "rm -f "
#define SYSTEM_CP "cp -f "
#define SYSTEM_MKDIR "mkdir "

#endif 

#if MAVEN_OS == 2

#define SYSTEM_RM "del -f "
#define SYSTEM_CP "copy -y "
#define SYSTEM_MKDIR "mkdir "

#endif