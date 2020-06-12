#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2048

sem_t mutex, wrt;
int rc, reader_no;

void* reader(void *);
void* writer(void *);

int main(int argc, char const *argv[]) {
	char *filename = (char *)calloc(MAX, sizeof(char));
	printf("Enter file name: ");
	fgets(filename, MAX, stdin);
	filename[strlen(filename)-1] = '\0';

	rc = 0; reader_no = 0;
	

	int nr, nw, i, j;
	printf("Enter max no. of Readers: ");
	scanf("%d", &nr);
	pthread_t read[nr];

	printf("Enter max no. of Writers: ");
	scanf("%d", &nw);
	pthread_t write[nw];
	getchar();

	sem_init(&wrt, 0, 1);
	sem_init(&mutex, 0, 1);

	for (i = 0, j = 0; i < nr || j < nw; ) {
		if (j < nw) {
			
			pthread_create(&write[j], NULL, writer, filename);
			j++;
			
		}
		
		
		if (i < nr) {
			
			pthread_create(&read[i], NULL, reader, filename);
			i++;
			
		}
		sleep(1);		
	}

	for (i = 0; i < nr; i++) {
		pthread_join(read[i], NULL);
	}

	for (j = 0; j < nw; j++) {
		pthread_join(write[j], NULL);
	}

	sem_destroy(&mutex);
	sem_destroy(&wrt);

	return 0;
}

void* reader(void *args) {
	
	sem_wait(&mutex);
	
	rc++; // increasing reader count by 1
	reader_no++;
	int rno = reader_no;
	if (rc == 1) {
		sem_wait(&wrt);
	}
	sem_post(&mutex);
	printf("FILE CONTENTS START HERE :::::::::::::::::::::::::::::::::::::::>\n");

	// critical section
	char *filename = (char *)args;
	FILE *fp = fopen(filename, "r");

	do {
		char line[MAX];
		fgets(line, MAX, fp);
		if(feof(fp)) {
			break;
		}
		printf("READER %d>>> %s", rno, line);
	} while (!feof(fp));

	fclose(fp);

	sem_wait(&mutex);
	rc--;
	if (rc == 0) {
		sem_post(&wrt);
	}
	sem_post(&mutex);
	pthread_exit(0);
}

void* writer(void *args) {
	sem_wait(&wrt);

	char *filename = (char *)args;

	FILE *fp = fopen(filename, "a");

	printf("Enter the data to be written: ");
	char buffer[MAX];
	fgets(buffer, MAX, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	

	fprintf(fp, "%s\n", buffer);

	fclose(fp);

	sem_post(&wrt);
	pthread_exit(0);
}