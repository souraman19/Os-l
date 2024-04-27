// Write a program in C where a Parent process communicates with its child 
// process via pipe command such that upon receipt of the message, the child 
// process changes its case and returns the message (via a pipe) to the parent, 
// where it is then displayed. Note: On a system that does not support duplex 
// pipes, you will need to generate two pipes prior to forking the child proces

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>

#define READ_END 0
#define WRITE_END 1

int main(){
    
    int fd1[2];
    int fd2[2];
    pid_t pid;
    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        printf("unsuccessful pipe creation");
        return 1;
    }
    pid = fork();
    if(pid == -1){
        printf("fork unsuccessful");
        return 1;
    } else if(pid > 0){
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);

        char message[1000];
        printf("\nEnter the message:");
        fgets(message, sizeof(message), stdin);

        write(fd1[WRITE_END], &message, sizeof(message));
        close(fd1[WRITE_END]);

        read(fd2[READ_END], &message, sizeof(message));
        close(fd2[READ_END]);
        printf("\nThe changed message is : %s", message);


    } else {
        close(fd1[WRITE_END]);
        close(fd2[READ_END]);

        char received_message[1000];
        read(fd1[READ_END], &received_message, sizeof(received_message));
        close(fd1[READ_END]);

        for(int i = 0; i < strlen(received_message); i++){
            if(islower(received_message[i])){
                received_message[i] = toupper(received_message[i]);
            } else {
                received_message[i] = tolower(received_message[i]);
            }
        }

        write(fd2[WRITE_END], &received_message, sizeof(received_message));
        close(fd2[WRITE_END]);

    }

    return 0;
}