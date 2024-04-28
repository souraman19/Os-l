#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define BUFFER_SIZE 10
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 10
#define NUM_PRODUCER_ITERATIONS 20
#define NUM_CONSUMER_ITERATIONS 10


struct Monitor{
    int buffer[BUFFER_SIZE];
    int in, out;
    pthread_mutex_t mutex;
    pthread_cond_t empty, full;
} monitor;

void initMonitor(struct Monitor* m){
    m->in = 0;
    m->out = 0;
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->empty, NULL);
    pthread_cond_init(&m->full, NULL);
}

void* producer(void* args){
    int process_Id = *((int *)args);

    for(int i = 0; i < NUM_CONSUMER_ITERATIONS; i++){
        pthread_mutex_lock(&monitor.mutex);
        
        while((monitor.in + 1)% BUFFER_SIZE == monitor.out){
            pthread_cond_wait(&monitor.empty, &monitor.mutex);
        }

        monitor.buffer[monitor.in] = process_Id * 100 + i;
        printf("Producer %d produces %d\n", process_Id, monitor.buffer[monitor.in]);
        monitor.in = (monitor.in + 1)%BUFFER_SIZE;

        pthread_mutex_unlock(&monitor.mutex);
        pthread_cond_signal(&monitor.full);

        usleep(100000);
    }
    pthread_exit(NULL);
}

void *consumer(void* args){
    int process_id = *((int *) args);


    for(int i = 0; i < NUM_CONSUMER_ITERATIONS; i++){
        pthread_mutex_lock(&monitor.mutex);

        while(monitor.in == monitor.out){
            pthread_cond_wait(&monitor.full, &monitor.mutex);
        }

        int item = monitor.buffer[monitor.out];
        printf("consumer %d gets %d\n", process_id, item);
        monitor.out = (monitor.out + 1)%BUFFER_SIZE;

        pthread_cond_signal(&monitor.empty);
        pthread_mutex_unlock(&monitor.mutex);

        usleep(100000);
    }

    pthread_exit(NULL);
}


int main(){
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    initMonitor(&monitor);

    int producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];
    for(int i = 0; i < NUM_PRODUCERS; i++){
        producer_ids[i] = i+1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    for(int i = 0; i < NUM_CONSUMERS; i++){
        consumer_ids[i] = i+1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    for(int i = 0; i < NUM_PRODUCERS; i++){
        pthread_join(producers[i], NULL);
    }

    for(int i = 0; i < NUM_CONSUMERS; i++){
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.empty);
    pthread_cond_destroy(&monitor.full);
    return 0;
}