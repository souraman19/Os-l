// . Write a program in C that creates a child process, waits for the termination of the child and lists 
// process ID (PID), together with the state in which the process was terminated (in decimal and 
// hexadecimal)


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  
#include<sys/wait.h>
#include<sys/types.h>

int main(){
    pid_t pid;
    int status;
    pid = fork();
    if(pid == -1){
        printf("fork not successful");
        return 1;
    } else if(pid == 0){
        printf("Child process with pid: %d\n", getpid());

        sleep(2);
        exit(EXIT_SUCCESS);
    } else {
        printf("PARENt process with pid: %d\n", getpid());
        pid_t terminated_pid = waitpid(pid, &status, 0);
        if(terminated_pid == -1){
            printf("error");
            return 1;
        }
        if(WIFEXITED(status)){
            printf("child exited normally with status: %d (0x%x)", WEXITSTATUS(status), WEXITSTATUS(status));
        } else if(WIFSIGNALED(status)){
            printf("child exted by signal: %d (0x%x)", WTERMSIG(status), WTERMSIG(status));
        }
    }
    return 0;
}