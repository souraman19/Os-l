// The Collatz conjecture concerns what happens when we take any positive integer n and apply the 
// following algorithm: n = n/2, if n is even n = 3 × n + 1, if n is odd. The conjecture states that when 
// this algorithm is continually applied, all positive integers will eventually reach 1. For example, if n 
// = 35, the sequence is 35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1. Write a C program using the 
// fork() system call that generates this sequence in the child process. The starting number will be 
// provided from the command line. For example, if 8 is passed as a parameter on the Command line, 
// the child process will output 8, 4, 2, 1. Because the parent and child processes have their own copies 
// of the data, it will be necessary for the child to output the sequence. Have the


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid == -1){
        printf("fork unsuccessful");
    } else if(pid == 0){
        int n;
        printf("in the child\n");
        printf("Enter the value of n: ");
        scanf("%d", &n);
        printf("The seq is : %d ", n);
        while(n > 1){
            if(n%2 == 0){
                n /= 2;
                printf("%d ", n);
            } else{
                n = 3*n + 1;
                printf("%d ", n);
            }
        }
        exit(EXIT_SUCCESS);
    } else {
        printf("In the parent process \n");
        int status;
        waitpid(pid, &status, 0);
        printf("Child exited");
        printf("parent exited");
    }
    return 0;
}