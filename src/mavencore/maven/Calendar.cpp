#include "Calendar.h"
#include "Date.h"

#include <sys/time.h>
#include <cmath>

namespace maven {
	
	Calendar::Calendar() {
		super("maven.Calendar");
	}
	
	mdouble Calendar::epochSeconds() {
		return (mdouble) std::time(NULL);
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
	
	mdouble Calendar::runtime() {
		return (mdouble) clock() / (mdouble) CLOCKS_PER_SEC;
	}
	
}
