// Create a function removeNonAlphabets (char * inputFileName, char * outputFileName) in C that is passed 
// with parameters: an input file name and an output file name. The function then reads the input file using read system 
// call and removes all non-alphabets. It then writes the data to output file using write system call. You will need to 
// utilize open, read, write, and close system calls in this program. 


#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

void removeAlphabets(const char* sourcefile, const char* destinationfile){
    int inputFd, outputFd;
    char buff[1024];
    ssize_t bytes_read;
    ssize_t bytes_write;

    inputFd = open(sourcefile, O_RDONLY);
    if(inputFd == -1){
        printf("error");
        return ;
    }
    outputFd = open(destinationfile, O_WRONLY );
    if(outputFd == -1){
        printf("error");
        return ;
    }

    while((bytes_read = read(inputFd, buff, sizeof(buff))) > 0){
        for(ssize_t i = 0; i < bytes_read; i++){
            char c = buff[i];
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
              bytes_write =   write(outputFd, &c, 1);
                if(bytes_write == -1){
                    printf("error");
                    close(inputFd);
                    close(outputFd);
                    return;
                }
            }
        }
    }

    if(bytes_read == -1){
        printf("not success");
    }

    printf("success");
    close(inputFd);
    close(outputFd);

    return;

}

int main(){
    removeAlphabets("new.txt", "new2.txt");
    return 0;
}