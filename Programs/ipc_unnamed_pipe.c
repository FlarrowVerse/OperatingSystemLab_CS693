#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define MAX 1024

int main() {
	int fd[2], bytesRead;
	char message [100]; /* Parent process’s message buffer */
	pipe(fd); /*Create an unnamed pipe*/
	if (fork() == 0) {
		printf("***************CHILD PROCESS**********************\n");
		close(fd[READ]); /* Close unused end*/

		printf("Enter a message: ");
		char *phrase = (char *)calloc(MAX, sizeof(char));
		fgets(phrase, MAX, stdin);

		write(fd[WRITE], phrase, strlen ( phrase) +1); /* include NULL*/
		close(fd[WRITE]); /* Close used end*/
		printf("***************CHILD PROCESS END**********************\n");
	} else {
		printf("***************PARENT PROCESS**********************\n");
		close(fd[WRITE]); /* Close unused end*/ 
		bytesRead = read(fd[READ], message, 100);
		printf ("Read %d bytes: %s\n", bytesRead, message);
		close ( fd[READ]); /* Close used end */
		printf("***************PARENT PROCESS END**********************\n");
	}

}
