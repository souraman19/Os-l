#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/stat.h>

#define FIFO_NAME "/tmp/mypipe"
#define BUFFER_SIZE 256

int main(){
    char buffer[BUFFER_SIZE];
    int fd;

    fd = open(FIFO_NAME, O_WRONLY);
    if(fd == -1){
        printf("Failed to open pipe");
        return 1;
    }
    printf("Opening the pipe...%s.\n", FIFO_NAME);
    while (1)
    {
      printf("Enter the input: ");
      fgets(buffer, BUFFER_SIZE, stdin);
      buffer[strcspn(buffer, "\n")] = '\0';
      printf("Writing to the pipe...");
      ssize_t bytes_written = write(fd, buffer, strlen(buffer));
      if(bytes_written == -1){
        printf("Error in writing to pipe");
        close(fd);
        return 1;
      }
      printf("done\n");
      if(strcmp(buffer, "exit") == 0){
    
        printf("Exiting");
        break;
      }
    }
    
    return 0;
}