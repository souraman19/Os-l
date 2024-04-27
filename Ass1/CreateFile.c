#include<stdio.h>
#include<stdlib.h>

void createFile(const char* filename){
    FILE *file = fopen(filename, "w");
    if(file){
        printf("FILE created successFULLY");
        fclose(file);
    } else{
        printf("Unsuccessful");
    }
}

int main(){
    createFile("myCreatedFile1.txt");
    return 0;
}