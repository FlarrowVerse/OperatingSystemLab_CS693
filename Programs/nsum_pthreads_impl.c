#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct thread_data {
	pthread_t thread_id;
	int thread_num;
	int start;
	int end;
	int hop;
	int sum;
} thread_data;

// runner of each thread
void *sum_runner(void *);

int main(int argc, char *argv[]) {

	thread_data *threads;
	int sum = 0, thread_count = 2; // default values
	int N, hop = 2, i;

	if (argc == 1) { // default parameters
		N = 100;
	} 
	else if (argc == 2) { // range upper limit fixed
		N = atoi(argv[1]);
	} else { // both range and hop limits fixed
		N = atoi(argv[1]);
		hop = atoi(argv[2]);
	}

	thread_count = (N % hop != 0)? (N / hop) + 1:(N / hop);
	threads = (thread_data *)calloc(thread_count, sizeof(thread_data));

	for (i = 0; i < thread_count; i++) {
		// setting data to be transferred to the thread
		threads[i].thread_num = i + 1;
		threads[i].start = 1 + (i * hop);
		threads[i].end = threads[i].start + hop - 1;
		threads[i].end = (threads[i].end <= N)? threads[i].end: N;
		threads[i].hop = hop;
		threads[i].sum = 0;

		// thread creation
		int ret_status = pthread_create(&threads[i].thread_id, NULL, &sum_runner, &threads[i]);
		if (ret_status != 0) {
			fprintf(stderr, ">pthread_create: %d\n", ret_status);
		} else {
			printf("Thread %d creation and start success....\n", threads[i].thread_num);
		}
	}

	// waiting for threads to terminate
	for (i = 0; i < thread_count; i++) {
		int ret_status = pthread_join(threads[i].thread_id, NULL);
		if (ret_status != 0) {
			fprintf(stderr, ">pthread_join: %d\n", ret_status);
			exit(EXIT_FAILURE);
		} else {
			sum += threads[i].sum;
		}
	}

	printf("Sum of %d natural numbers are: %d\n", N, sum);

	return 0;
}

void *sum_runner(void *data) {
	thread_data *pt_data = data;
	int i, sum = 0;

	for (i = pt_data->start; i <= pt_data->end; i++) {
		sum += i;
	}
	pt_data->sum = sum;
	printf("Thread[%d]: sum(%d -> %d) = %d\n", pt_data->thread_num, pt_data->start, pt_data->end, pt_data->sum);
	pthread_exit(0);
}