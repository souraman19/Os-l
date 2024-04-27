//  Write a program to print characters starting from 15th character till the 20th character of file F1.txt into the file 
// F2.txt

#include<stdio.h>
#define BUFFER_SIZE 6

int main(){
    FILE* src;
    FILE* dst;
    char buff[BUFFER_SIZE+1];
    size_t bytes_read;
    src = fopen("new.txt", "r");
    if(src == NULL){
        printf("Error in opeing files");
        return 1;
    }

    dst = fopen("new2.txt", "w");
    if(dst == NULL){
        printf("Error in opening file");
        fclose(src);
        return 1;
    }

    fseek(src, 14, SEEK_SET);
    bytes_read = fread(buff, 1, BUFFER_SIZE, src);
    if(bytes_read == 0){
        printf("Error");
        fclose(src);
        fclose(dst);
        return 1;
    }

    buff[bytes_read] = '\0';

    fwrite(buff, 1, bytes_read, dst);
    fclose(src);
    fclose(dst);



     printf("Success: Copied characters from one to another\n");
    return 0;
}