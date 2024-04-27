#include<stdio.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX_NUMBERS 100

int numbers[MAX_NUMBERS];
int count;

void *calculate_avg(void* args){
    double sum = 0;
    for(int i = 0; i < count; i++){
        sum += numbers[i];
    }
    double avg = sum/count;
    printf("The avg value is %.2f\n", avg);
    pthread_exit(NULL);
}

void *calculate_minimum(void* args){
    int minm = numbers[0];
    for(int i = 0; i < count; i++){
        if(numbers[i] < minm){
            minm = numbers[i];
        }
    }
    printf("The minimum number is %d", minm);
    pthread_exit(NULL);
}

void *calculate_maximum(void* args){
    int maxm = numbers[0];
    for(int i = 0; i < count; i++){
        if(numbers[i] > maxm){
            maxm = numbers[i];
        }
    }
    printf("The minimum number is %d", maxm);
    pthread_exit(NULL);
}

int main(){
    printf("Enter the number of elements");
    scanf("%d", &count);

    //also check if count is greater tnan max_size or less than 0

    printf("Enter elements:");
    for(int i = 0; i < count; i++){
        scanf("%d", &numbers[i]);
    }

    pthread_t threads[3];
    pthread_create(&threads[0], NULL, calculate_avg, NULL);
    pthread_create(&threads[1], NULL, calculate_maximum, NULL);
    pthread_create(&threads[2], NULL, calculate_minimum, NULL);
    
    for(int i = 0; i < 3; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}