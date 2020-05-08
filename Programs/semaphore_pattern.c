#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t sem;
int max;
int charCount;

void* thread_proc(void *);

int main() {

	printf("Enter max length of pattern: ");
	scanf("%d", &max);

	sem_init(&sem, 0, 1); // initialising semaphore to value 1
	pthread_t proc_1, proc_2;
	int thread_1 = 1, thread_2 = 2;
	charCount = 0;

	pthread_create(&proc_1, NULL, thread_proc, &thread_1);

	pthread_create(&proc_2, NULL, thread_proc, &thread_2);

	// wait for the threads to join back with main thread
	pthread_join(proc_1, NULL);
	pthread_join(proc_2, NULL);

	sem_destroy(&sem);
	printf("\n");

	return 0;
}

void* thread_proc(void *arg) {
	int *tNum = arg, i;
	if (*tNum == 1) {
		// for thread 1
		while (charCount < max) {
			sem_wait(&sem);
			printf("b"); charCount++;
			if(charCount >= max) {
				sem_post(&sem);
				break;
			}

			printf("a"); charCount++;
			if(charCount >= max) {
				sem_post(&sem);
				break;
			}
			sem_post(&sem);
			usleep(100);
		}
	} else {
		// for thread 2
		while (charCount < max) {
			sem_wait(&sem);
			printf("a"); charCount++;
			if(charCount >= max) {
				sem_post(&sem);
				break;
			}

			printf("b"); charCount++;
			if(charCount >= max) {
				sem_post(&sem);
				break;
			}
			sem_post(&sem);
			usleep(100);
		}
	}
}