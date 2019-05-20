#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>

int main() {
	char date1[20], date2[20];
	struct tm stamp1, stamp2;
	fgets(date1, sizeof(date1), stdin);
	memset(&stamp1, 0, sizeof(struct tm));
	memset(&stamp2, 0, sizeof(struct tm));
	strptime(date1, "%Y-%m-%d %H:%M", &stamp1);
	stamp1.tm_isdst = -1;
	stamp2.tm_isdst = -1;
	time_t time1 = mktime(&stamp1), time2;
	fgets(date2, sizeof(date2), stdin);
	do {
		strptime(date2, "%Y-%m-%d %H:%M", &stamp2);
		time2 = mktime(&stamp2);
		printf("%lld\n", (int64_t)(time2 - time1) / 60);
		time1 = time2;
	} while (fgets(date2, sizeof(date2), stdin));
	return 0;
}
