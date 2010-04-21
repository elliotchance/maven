/*
 *  maven Programming Language
 *  Created by Elliot Chance <elliot@chancemedia.com>.
 */

#include "maven.h"

string nativeToObject(string type) {
	if(type == "boolean")
		return "maven.Boolean";
	if(type == "byte")
		return "maven.Byte";
	if(type == "char")
		return "maven.Character";
	if(type == "double")
		return "maven.Double";
	if(type == "float")
		return "maven.Float";
	if(type == "int")
		return "maven.Integer";
	if(type == "long")
		return "maven.Long";
	if(type == "quad")
		return "maven.Quad";
	if(type == "short")
		return "maven.Short";
	
	return "maven.Object";
}
