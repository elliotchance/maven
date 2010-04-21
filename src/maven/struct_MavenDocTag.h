/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#ifndef _MAVEN_STRUCT_DOCTAG_H
#define _MAVEN_STRUCT_DOCTAG_H 1

#include "maven.h"
#include "struct_StringList.h"

struct MavenDocTag {
	
	/**
	 * @brief The main body of the documentation.
	 */
	string body;
	
	/**
	 * @brief \@brief.
	 */
	string tagBrief;
	
	/**
	 * @brief \@param.
	 */
	StringList tagParam;
	
	/**
	 * @brief \@return.
	 */
	string tagReturn;
	
	/**
	 * @brief \@since.
	 */
	string tagSince;
	
	/**
	 * @brief \@throws.
	 */
	StringList tagThrows;
	
	/**
	 * @brief \@version.
	 */
	string tagVersion;
};

#endif
