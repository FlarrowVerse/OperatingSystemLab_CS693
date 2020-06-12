#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_FILE "FIFO_BUFF"
#define MAX 1024

int main() {
   int fd;
   char *buffer_1 = (char *)calloc(MAX, sizeof(char)), *buffer_2 = (char *)calloc(MAX, sizeof(char));
   char *result = (char *)calloc(MAX, sizeof(char));
   
   int read_bytes;
   
   /* Create the FIFO if it does not exist */
   mkfifo(FIFO_FILE, S_IFIFO|0640);
   fd = open(FIFO_FILE, O_RDWR);
   
   read_bytes = read(fd, buffer_1, sizeof(buffer_1));
   buffer_1[read_bytes] = '\0';
   printf("Received string: \"%s\" and length is %d\n", buffer_1, (int)strlen(buffer_1));

   read_bytes = read(fd, buffer_2, sizeof(buffer_2));
   buffer_2[read_bytes] = '\0';
   printf("Received string: \"%s\" and length is %d\n", buffer_2, (int)strlen(buffer_2));

   strcpy(result, (strcmp(buffer_1, buffer_2) == 0)? "same": "not same");
   result[strlen(result)] = '\0';   
   write(fd, result, strlen(result) + 1);
   printf("Sent result: \"%s\" \n", result);

   return 0;
}
