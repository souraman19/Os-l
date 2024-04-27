// Write a program that calls fork ( ) system call. Before calling fork ( ), have the main process access 
// a variable (e.g., x) and set its value to something (e.g., 1000). What value is the variable in the child 
// process? What happens to the variable when both the child and parent change the value of x?
// Clearly write your observations.


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
    pid_t pid;
    pid = fork();
    int x = 40;
    if(pid == -1){
        printf("fork unsuccessful");
        return 1;
    } else if(pid == 0){
        printf("child process\n");
        x *= 3;
        printf("Value of x in child: %d", x);
        exit(EXIT_SUCCESS);
    } else {
        printf("parent process\n");
        int status;
        waitpid(pid, &status, 0);
        x += 10;
        printf("Value of x in parent %d", x);
    }
    return 0;
}