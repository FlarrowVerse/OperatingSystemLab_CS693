#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define true 1
#define false 0

void signal_handler(int);

int main() {

	signal(SIGINT, signal_handler);
	while(true) {
		printf("Go Beyond! Plus Ultra!!!\n");
		sleep(1);
	}
	return 0;
}

void signal_handler(int sigNo) {
	printf("Signal caught::: %d\n", sigNo);
	sleep(1);
	exit(0);
}