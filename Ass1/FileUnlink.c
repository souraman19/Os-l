#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void unlinkFile(const char* file){
    if(unlink(file) == 0){
        printf("Unlink success");
    } else {
        printf("Unlink not successful");
    }
}

int main(){
    unlinkFile("myCreatedFile1.txt");
    return 0;
}