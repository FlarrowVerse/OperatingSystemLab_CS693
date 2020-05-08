#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define true 1
#define false 0

static int alarm_fired = false;
int isLeapYear(int);
void leapCheck_handler(int);

int main(int argc, char *argv[]) {

	printf("At regular intervals check for leap year.....\n");
	int pid = fork(), time = 5;
	if (argc > 1) {
		time = atoi(argv[1]);
	}

	if (pid == -1) {
		perror("child thread creation failed.\n");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) { // child thread firing alarm
		while (alarm_fired != true) {
			signal(SIGALRM, leapCheck_handler);
			pause();
			printf("Waiting for next slot....\n");
		}		
		
	} else {		
		while (alarm_fired != true) {
			// printf("Waiting for the alarm to go off.....\n");
			sleep(time);
			kill(pid, SIGALRM);
		}
		printf("DONE.\n");
	}

	return 0;
}

int isLeapYear(int year) {
	return ((year%4 == 0 && year%100 != 0) || year%400 == 0)? true: false;
}

void leapCheck_handler(int sigNo) {

	int year;
	printf("Enter a year: ");
	scanf("%d", &year);
	if (isLeapYear(year) == true) {
		printf("%d is a leap year.\n", year);
	} else {
		printf("%d is not a leap year.\n", year);
	}
	printf("------------------------------------------------------\n");
}