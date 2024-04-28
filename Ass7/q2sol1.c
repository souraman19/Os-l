#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 10
#define PRODUCER_COUNT 5
#define CONSUMER_COUNT 10
#define PRODUCERS_ITERATIONS 20
#define CONSUMERS_ITERATIONS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void* producers(void* args){
    int process_Id = *((int *) args);

    for(int i = 0; i < PRODUCER_COUNT; i++){
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = process_Id * 100 + i;
        printf("Producer %d produces the item %d\n", process_Id, buffer[in]);
        in = (in+1)%BUFFER_SIZE;

        sem_post(&full);
        sem_post(&mutex);

        usleep(100000);
    }
    pthread_exit(NULL);
}


void* consumers(void* args){
    int process_Id = *((int *) args);
    for(int i = 0; i < CONSUMERS_ITERATIONS; i++){
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumer %d get item %d\n", process_Id, item);
        out = (out + 1)%BUFFER_SIZE;


        sem_post(&empty);
        sem_post(&mutex);

        usleep(100000);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t prodcers[PRODUCER_COUNT], consmers[CONSUMER_COUNT];
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    int producer_ids[PRODUCER_COUNT];
    for(int i = 0; i < PRODUCER_COUNT; i++){
        producer_ids[i] = i + 1;
        producers(&prodcers[i], NULL, prodcers, &producer_ids[i]);
    }
    int consumer_ids[CONSUMER_COUNT];
    for(int i = 0; i < CONSUMER_COUNT; i++){
        consumer_ids[i] = i+1;
        consmers(&consmers[i], NULL, consmers, &consumer_ids);
    }
    for(int i = 0; i < PRODUCER_COUNT; i++){
        pthread_join(prodcers[i], NULL);
    }
    for(int i = 0; i < CONSUMER_COUNT; i++){
        pthread_join(consmers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}