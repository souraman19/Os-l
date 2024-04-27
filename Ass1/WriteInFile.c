#include<stdio.h>
#include<stdlib.h>

void wrtieInFile(const char* filename, const char* content){
    FILE *file = fopen(filename, "w");
    if(file){
        fprintf(file, "%s\n", content);
        printf("success");
        fclose(file);
    } else{
        printf("Unsuccessful");
    }
}

int main(){
    wrtieInFile("myCreatedFile1.txt", "I am a gamer");
    return 0;
}