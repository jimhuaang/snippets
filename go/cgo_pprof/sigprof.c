#include "sigprof.h"

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int sleep_10s() {
	time_t start = time(NULL);
	while (time(NULL) < start + 10) {
		char buffer[26];
		struct tm *tm_info;
		time_t timer;
		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		puts(buffer);

		sleep(1);
	}
}

int main() {
	// option 2: mannual profile collection.
	// start
	go_start_cpuprofile();

	//option 1: ideal solution for network servers
	//go_listenAndServe();
	
	go_leakyFunc();
	go_memprofile();  // option 2 for mem profile
	sleep_10s();

	// option 2: mannual profile collection. 
	// stop
	go_stop_cpuprofile();
	return 0;
}


