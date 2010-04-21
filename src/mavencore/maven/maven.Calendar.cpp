#include "maven.Calendar.h"
#include "maven.Date.h"

namespace maven {
	
	Calendar::Calendar() {
		super("maven.Calendar");
	}
	
	maven_int Calendar::epochSeconds() {
		return time(NULL);
	}
	
	maven_int Calendar::epochDays() {
		return (maven_int) floor((maven_double) time(NULL) / 86400);
	}
	
	maven::Date* Calendar::now() {
		maven::Date* d = new maven::Date();
		time_t rawtime;
		time(&rawtime);
		struct tm* timeinfo = localtime(&rawtime);
		d->year = timeinfo->tm_year + 1900;
		d->month = timeinfo->tm_mon;
		d->day = timeinfo->tm_mday;
		d->hour = timeinfo->tm_hour;
		d->minute = timeinfo->tm_min;
		d->second = timeinfo->tm_sec;
		return d;
	}
	
	maven_double Calendar::runtime() {
		return (maven_double) clock() / (maven_double) CLOCKS_PER_SEC;
	}
	
}
