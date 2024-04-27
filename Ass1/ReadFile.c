#include<stdio.h>
#include<stdlib.h>

void readFile(const char* filename){
    FILE *file = fopen(filename, "r");
    if(file){
        char ch;
        while((ch = fgetc(file)) != EOF){
            putchar(ch);
        }
        fclose(file);
    } else {
        printf("cant open");
    }
}

int main(){
    readFile("myCreatedFile1.txt");
    return 0;
}