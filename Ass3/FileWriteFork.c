// Write a program that opens a file (with the open ( ) system call) and then calls fork ( ) to create a 
// new process. Can both the child and parent access the file descriptor returned by open ( )? What 
// happens when they are writing to the file concurrently, i.e., at the same time? Clearly write your 
// observations.


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int fd = open("new.txt", O_WRONLY);
    if(fd == -1){
        printf("error");
        return 1;
    }
    pid_t pid;
    pid = fork();
    if(pid == -1){
        printf("fork unsuccessful");
        return 1;
    } else if(pid == 0){
        printf("child process");
        const char* text = "I hate you";
        ssize_t bytes_written = write(fd, text, strlen(text));
        if(bytes_written == -1){
            printf("Error in writing file by child");
        }
        close(fd);
    } else {
        printf("parent process");
        const char* text2 = "I still love you";
        ssize_t bytes_wr = write(fd, text2, strlen(text2));
        if(bytes_wr == -1){
            printf("Error in writing file by parent");
        }
        close(fd);
    }
    // printf("success");
    return 0;
}