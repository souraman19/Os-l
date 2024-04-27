#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_SIZE 100
int n;
int counter = 0;
int present = 1;
int arr[MAX_SIZE];

void *calculate(void* args){
    present *= arr[counter];
    counter++;
    printf("Product %d : %d\n", counter+1, present);
}

int main(){
    printf("Enter n:");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    pthread_t threads[n];
    for(int i = 0; i < n; i++){
        pthread_create(&threads[i], NULL, calculate, NULL);
    }

    for(int i = 0; i < n; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}