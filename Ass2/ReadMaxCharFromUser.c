//  Write a program to read a maximum of 15 characters from the user and print them on the screen.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    char c[16];
    printf("Enter characters: ");
    fgets(c, sizeof(c), stdin);
    printf("\nYou have entered: ");
    printf(c);
    return 0;
    
}

