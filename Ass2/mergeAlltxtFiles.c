// . Write a program to read all txt files (that is files that ends with .txt) in the current directory and merge them all 
// to one txt file and returns a file descriptor for the new file. 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>

void mergeTextFiles(const char* filename){
    char buffer[1024];
    FILE* outputfile;
    DIR *dir;
    struct dirent *entry;

    outputfile = fopen(filename, "w");
    if(outputfile == NULL){
        printf("not success");
        return 1;
    }

    dir = opendir(".");
    if(dir == NULL){
        printf("Error in opening directory");
        fclose(outputfile);
        return 1;
    }

    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL){
            FILE* inputfile = fopen(entry->d_name, "r");
            if(inputfile != NULL){
                while(fgets(buffer, sizeof(buffer), inputfile) != NULL){
                    fputs(buffer, outputfile);
                } 
                fclose(inputfile);  
            } else {
                printf("error");
            }
        }
    }
    closedir(dir);
    fclose(outputfile);

}

int main(){
    mergeTextFiles("new.txt");
    return 0;
}