#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void readReverse(const char* filename){
    FILE *file = fopen(filename, "r");
    if(file){
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        char ch;
        for(int i = size-1; i >= 0; i--){
            fseek(file, i, SEEK_SET);
            ch = fgetc(file);
            putchar(ch);
        }
        fclose(file);
    } else {
        printf("Unsuccess");
    }
}

int main(){
    readReverse("myCreatedFile1.txt");
    return 0;

}
