#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void filecopy(const char* s, const char* d){
    FILE *src = fopen(s, "r");
    FILE *dst = fopen(d, "w");
    if(src && dst){
        char ch;
        while((ch = fgetc(src)) != EOF){
            fputc(ch, dst);
        }
        fclose(src);
        fclose(dst);
        printf("success");
    } else {
        printf("Unsuccess");
    }
}

int main(){
    filecopy("myCreatedFile1.txt", "myCreatedFile2.txt");
    return 0;
}