#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <math.h>

void* thread_proc(void *);

int main() {

	pthread_t prime_thread;
	void **result = (void **)malloc(sizeof(void *));
	int num;
	while (1) {
		printf("Enter a number: ");
		scanf("%d", &num);
		

		pthread_create(&prime_thread, NULL, thread_proc, &num);

		// wait for the threads to join back with main thread
		pthread_join(prime_thread, result); // eikhane void ** dite hocche as 2nd argument
		
		int retVal = *(int *)(*result); 
		printf("%d is %s prime number\n", num, (retVal)? "a": "not a");

		printf("Do you want to continue?(Y/N): "); getchar();
		char ch = getchar();
		if (ch == 'Y' || ch == 'y') {
			continue;
		}
		break;
	}	

	return 0;
}

void* thread_proc(void *arg) {
	int *tNum = arg, i;
	int *result = (int *)malloc(sizeof(int));
	*result = -1;
	
	for (i = 2; i <= sqrt(*tNum); i++) {
		if ((*tNum) % i == 0) {
			*result = 0;
		}
	}
	*result = (*result == -1)? 1: *result; // eta prime check er final result
	
	pthread_exit((void *)result); // sir ei prime check er result ta main e return korte chaichilam
}