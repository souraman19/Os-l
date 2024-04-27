//  Write a program using open () and lseek () system calls to print the last 5 characters of a file on the screen.


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFFER_SIZE 5

int main(){
    char buff[BUFFER_SIZE + 1] ;

    int fd, bytes_read;
    fd = open("new.txt", O_RDONLY);
    if(fd == -1){
        printf("Error in opening file");
        return 1;
    }

    if(lseek(fd, -5, SEEK_END) == -1){
        printf("Error in seeking file");
        return 1;
    }

    bytes_read = read(fd, buff, BUFFER_SIZE);
    if(bytes_read == -1){
        printf("Error in reading");
        return 1;
    }

    buff[bytes_read] = '\0';
    printf("Last 5 chracters %s", buff);

    return 0;
}