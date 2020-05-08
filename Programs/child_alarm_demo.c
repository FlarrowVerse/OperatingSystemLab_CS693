#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define true 1
#define false 0

static int alarm_fired = false;
void fire_alarm(int);

int main(int argc, char *argv[]) {

	printf("The clock is ticking! Time is running out.....\n");
	int pid = fork(), time = 6;
	if (argc > 1) {
		time = atoi(argv[1]);
	}

	if (pid == -1) {
		perror("child thread creation failed.\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) { // child thread firing alarm
		sleep(time);		
		kill(getppid(), SIGALRM);
		printf("Parent process stopped.\n");
		exit(0);
	} else {
		printf("Waiting for the alarm to go off.....\n");
		signal(SIGALRM, fire_alarm);
		pause();
		if (alarm_fired == true) {
			printf("Alarm fired.\n");
		}
		printf("DONE.\n");
	}

	// signal(SIGINT, signal_handler);
	// while(true) {
	// 	printf("Go Beyond! Plus Ultra!!!\n");
	// 	sleep(1);
	// }
	return 0;
}

void fire_alarm(int sigNo) {
	// printf("Signal caught::: %d\n", sigNo);
	// sleep(1);
	// exit(0);
	alarm_fired = true;
}