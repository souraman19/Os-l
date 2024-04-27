#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_SIZE 100
int n;
int arr[MAX_SIZE];

void *fibon(void* args){
    if(n == 0){
        printf("%d", 0);
        return NULL;
    } 
    if(n == 1){
        printf("%d %d", 0, 1);
        return NULL;
    }
    arr[0] = 0;
    arr[1] = 1;
    int first = 0;
    int second = 1;
    for(int i = 2; i <= n; i++){
        int temp = first + second;
        first = second;
        second = temp;
        arr[i] = temp;
    }
    pthread_exit(NULL);
}

int main(){
    scanf("%d", &n);
    pthread_t p;
    pthread_create(&p, NULL, fibon, NULL);
    pthread_join(p, NULL);
    printf("\n");
    for(int i = 0; i <= n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}