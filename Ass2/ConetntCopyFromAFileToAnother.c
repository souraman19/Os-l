// Write a program to read some content (20 characters) of file F1.txt into file F2.txt. The contents of file F2 
// should not get deleted or overwritten.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    char c[20];
    FILE* src = fopen("a.txt", "r");
    FILE* dst = fopen("b.txt", "a");

    if(src == 0){
        printf("error");
        return 1;
    }
    if(dst == 0){
        printf("error");
        return 1;
    }
    fputs(c, dst);
    // while(fgets(c, sizeof(c), src) != NULL){
    //     fputs(c, dst);
    // }

    fclose(src);
    fclose(dst);
    printf("Success");
    return 0;
}