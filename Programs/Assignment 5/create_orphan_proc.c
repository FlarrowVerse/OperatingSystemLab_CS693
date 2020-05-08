#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

        pid_t pid, cpid, ppid;
        pid = getpid();
        printf("Before fork: PID of main process: %d\n", pid);

        pid = fork();

        if (pid < 0) {
                printf("ERROR: fork() failed! child process not created.\n");
                return 1;
        }

        if (pid == 0) {
                // child process
                printf("This is the child process.\n");
                cpid = getpid();
                ppid = getppid();

                printf("Current child process ID: %d, Parent process ID: %d\n", cpid, ppid);
		sleep(10); // child sleeps while parent gets killed
		printf("Orphaned Process:: PID: %d, PPID: %d\n", getpid(), getppid());
        } else {
                // parent process
                printf("This is the parent process.\n");
                cpid = getpid();
                ppid = getppid();
                printf("Current process ID: %d, Parent process ID: %d\n", cpid, ppid);
                printf("Newly created child PID: %d\n", pid);
		sleep(5); // parent process wait time
		printf("Parent process killed....\n");
        }

        return 0;
}

