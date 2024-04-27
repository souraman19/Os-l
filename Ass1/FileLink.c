#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void linkFile(const char* oldname, const char* newname){
    if(link(oldname, newname) == 0){
        printf("link successful"); 
    } else {
        printf("link unsuccess");
    }
}

int main(){
    linkFile("file1.txt", "file2.txt");
    return 0;
}