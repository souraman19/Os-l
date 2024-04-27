
//  Write a program to print characters starting from 15th character till the 20th character of file F1.txt into the file 
// F2.txt


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFFER_SIZE 6

int main(){
    char buff[BUFFER_SIZE + 1];
    int fd1, fd2, bytes_read;

    fd1 = open("new.txt", O_RDONLY);
    if(fd1 == -1){
        printf("unsuccessful");
        return 1;
    }

    fd2 = open("new2.txt", O_WRONLY);
    if(fd2 == -1){
        close(fd1);
        printf("unsuccessful");
        return 1;
    }

    if(lseek(fd1, 14, SEEK_SET) == -1){
        printf("not suceess");
        return 1;
    }

    bytes_read = read(fd1, buff, BUFFER_SIZE);
    if(bytes_read == -1){
         close(fd1);
          close(fd2);
        printf("unsuccess");
        return 1;
    }

    

    buff[bytes_read] = '\0';

    if(write(fd2, buff, bytes_read) == -1){
        close(fd1);
          close(fd2);
        printf("unsuccess");
        return 1;
    }

    close(fd1);
    close(fd2);
    printf("success %s", buff);

    return 0;
}