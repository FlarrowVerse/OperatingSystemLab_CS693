#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 2048

typedef struct BUFFER {
	char **data;
	int size;
	int front, rear; // int curr;
} buffer;

sem_t S,E,F;

char* produce(int);
void append(buffer *, char *);
char* take(buffer *);
void use(char *);

void* thread_consumer(void *);
void* thread_producer(void *);

int main(int argc, char const *argv[]) {
	pthread_t consumer, producer;

	/* initializing the buffer shared between producer-consumer */
	buffer *buff = (buffer *)malloc(sizeof(buffer));
	printf("BUFFER SIZE AVAILABLE(max. value is 2048 bytes)::: ");
	scanf("%d", &(buff->size)); getchar();
	buff->front = -1, buff-> rear = -1; // buff->curr = 0;
	buff->data = (char **)calloc(buff->size, sizeof(char *));
	int i;
	for (i = 0; i < buff->size; i++) {
		buff->data[i] = (char *)calloc(MAX, sizeof(char)); // each record of the produce list
	}

	sem_init(&S, 0, 1); // semaphore to sync the producer-consumer processes
	sem_init(&E, 0, buff->size); // semaphore to sync between producer-consumer when buffer is empty
	sem_init(&F, 0, 0); // semaphore to sync between producer-consumer when buffer is full

	pthread_create(&producer, NULL, thread_producer, buff); // producer
	sleep(5);
	pthread_create(&consumer, NULL, thread_consumer, buff); // consumer

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	sem_destroy(&S);
	sem_destroy(&E);
	sem_destroy(&F);

	return 0;
}

char* produce(int size) {
	printf("Name a product(NA to stop production): ");
	char *input = (char *)calloc(MAX, sizeof(char));
	fgets(input, MAX, stdin);
	input[strlen(input)-1] = '\0';
	return input;
}

void append(buffer *buff, char *data) {
	// strcpy(buff->data[buff->curr], data);
	strcpy(buff->data[(buff->rear + 1) % buff->size], data);
	// printf("Inserted item \"%s\" at position \"%d\"\n", buff->data[buff->curr], buff->curr);
	buff->rear = (buff->rear + 1) % buff->size;
}

void* thread_producer(void *args) {
	buffer *buff = args;
	while(1) {
		
		sem_wait(&E);
		sem_wait(&S);
		char *product = produce(buff->size);
		append(buff, product);
		sem_post(&S);
		sem_post(&F);
		sleep(1);
		
		if (strncmp("NA", product, 2) == 0) {
			break;
		}
	}
	pthread_exit(0);
}

char* take(buffer *buff) {
	char *data = (char *)calloc(MAX, sizeof(char));
	// strcpy(data, buff->data[buff->curr - 1]);
	// printf("Extracted \"%s\"\n", data);
	strcpy(data, buff->data[(buff->front + 1) % buff->size]);
	// strcpy(buff->data[buff->curr - 1], "");
	strcpy(buff->data[(buff->front + 1) % buff->size], "");
	// buff->data[buff->curr-1][0] = '\0';
	// buff->curr = buff->curr - 1;
	buff->data[(buff->front + 1) % buff->size][0] = '\0';
	buff->front = (buff->front + 1) % buff->size;
	return data;
}

void use(char *data) {
	printf("CONSUMER SAYS> Product consumed: %s\n\n", data);	
}

void* thread_consumer(void *args) {
	buffer *buff = args;
	while(1) {
		sem_wait(&F);
		sem_wait(&S);		
		char *product = take(buff);
		use(product);
		sem_post(&S);
		sem_post(&E);
		sleep(1);
		
		if (strncmp("NA", product, 2) == 0) {
			break;
		}
	}
	pthread_exit(0);
}