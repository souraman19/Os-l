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
    mkfifo(FIFO_NAME, 0666);
    printf("Creating the pipe name :%s\n", FIFO_NAME);
    fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1){
        printf("Error in opening pipe");
        return 1;
    }
    printf("Waiting for the input...\n");
    while (1)
    {
        ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read == -1){
            printf("Error in reading from pipe");
            close(fd);
            return 1;
        }
        else if(bytes_read == 0){
            printf("Writer cloased the pipe...\n");
            printf("Exiting");
            break;
        } else {
            buffer[bytes_read] = '\0';
            printf("Got it : %s\n", buffer);
            if(strcmp(buffer, "exit") == 0){
                print("Exiting\n");
                break;
            }
        }
    }

    close(fd);
    unlink(FIFO_NAME);
    
    return 0;
}