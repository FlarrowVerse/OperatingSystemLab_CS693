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
   int len;
   char *buffer_1 = (char *)calloc(MAX, sizeof(char)), *buffer_2 = (char *)calloc(MAX, sizeof(char));
   char *result = (char *)calloc(MAX, sizeof(char));
   
   fd = open(FIFO_FILE, O_CREAT|O_RDWR);
   

   printf("Enter string 1: ");
   fgets(buffer_1, sizeof(buffer_1), stdin);
   len = strlen(buffer_1);
   buffer_1[len - 1] = '\0';
   write(fd, buffer_1, strlen(buffer_1));
   printf("Sent string: \"%s\" and string length is %d\n", buffer_1, (int)strlen(buffer_1));
   
   printf("Enter string 2: ");
   fgets(buffer_2, sizeof(buffer_2), stdin);
   len = strlen(buffer_2);
   buffer_2[len - 1] = '\0';
   write(fd, buffer_2, strlen(buffer_2));
   printf("Sent string: \"%s\" and string length is %d\n", buffer_2, (int)strlen(buffer_2));

   sleep(2);

   int read_bytes = read(fd, result, sizeof(result));
   result[read_bytes] = '\0';
   printf("Result recieved from server: %s\n", result);
   return 0;
}
