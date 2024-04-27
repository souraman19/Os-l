#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define ROW_SIZE 4
#define COL_SIZE 4

int A[ROW_SIZE][COL_SIZE];
int B[ROW_SIZE][COL_SIZE];

int sum[ROW_SIZE][COL_SIZE];
int diff[ROW_SIZE][COL_SIZE];

void* calSum(void* args){
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
}

void* calDiff(void* args){
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            diff[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main(){
    printf("Enter the elements of matrix A\n");
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            scanf("%d", &A[i][j]);
        }
    }
    printf("\nEnter for B:\n");
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            scanf("%d", &B[i][j]);
        }
    }

    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, calSum, NULL);
    pthread_create(&thread2, NULL, calDiff, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("sum:\n");
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }
    printf("diff:\n");
    for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COL_SIZE; j++){
            printf("%d ", diff[i][j]);
        }
        printf("\n");
    }

    return 0;
}