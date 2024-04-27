// Write a C program to show parent child process relation using fork () system 
// call in which Parent creates pipe, forks a child, and writes into pipe (the
// number whose factorial is to be calculated, take number from user), Child 
// reads from the pipe and compute and display factorial of a number written by 
// parent process


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int factorial(int n){
    if(n <= 0)
    return 1;

    return n * factorial(n-1);
}

int main(){
    pid_t pid;
    int fd[2];

    if(pipe(fd) == -1){
        printf("unsuccess");
        return 1;
    }
    pid = fork();
    if(pid == -1){
        printf("Fork unsuccessful");
    } else if(pid == 0){
        close(fd[WRITE_END]);
        int number;
        read(fd[READ_END], &number, sizeof(number));
        printf("The factorial of the number: %d", factorial(number));
        close(fd[READ_END]);
    } else {
        close(fd[READ_END]);
        int n;
        printf("Enter the number: ");
        scanf("%d", &n);
        write(fd[WRITE_END], &n, sizeof(n));
        close(fd[WRITE_END]);
    }
    return 0;
}