#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_RESOURCES 5 // Maximum available resources
#define MAX_PROCESSES 3 // Number of processes

int available_resources = MAX_RESOURCES;
int allocation[MAX_PROCESSES];
int max_need[MAX_PROCESSES];
int need[MAX_PROCESSES];
int process_completed[MAX_PROCESSES] = {0};

pthread_mutex_t mutex;

// Function to check if the system is in a safe state
int isSafe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int i, j;

    for (i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available_resources;
    }

    for (i = 0; i < MAX_PROCESSES; i++) {
        if (!process_completed[i]) {
            int safe = 1;
            for (j = 0; j < MAX_RESOURCES; j++) {
                if (need[i] > work[j]) {
                    safe = 0;
                    break;
                }
            }
            if (safe) {
                for (j = 0; j < MAX_RESOURCES; j++) {
                    work[j] += allocation[i];
                }
                finish[i] = 1;
            }
        }
    }

    for (i = 0; i < MAX_PROCESSES; i++) {
        if (!finish[i]) {
            return 0; // System is not in a safe state
        }
    }

    return 1; // System is in a safe state
}

// Function for a process to request resources
void *processRequest(void *arg) {
    int process_id = *((int *)arg);
    int request[MAX_RESOURCES];
    int i;

    // Generate random resource request
    for (i = 0; i < MAX_RESOURCES; i++) {
        request[i] = rand() % (max_need[process_id] + 1);
    }

    pthread_mutex_lock(&mutex);

    // Check if the request can be granted
    int safe = 1;
    for (i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_id][i]) {
            safe = 0;
            break;
        }
    }

    if (safe) {
        for (i = 0; i < MAX_RESOURCES; i++) {
            allocation[process_id][i] += request[i];
            need[process_id][i] -= request[i];
            available_resources -= request[i];
        }

        if (!isSafe()) {
            // Undo the allocation if it leads to an unsafe state
            for (i = 0; i < MAX_RESOURCES; i++) {
                allocation[process_id][i] -= request[i];
                need[process_id][i] += request[i];
                available_resources += request[i];
            }
        }
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_PROCESSES];
    int process_ids[MAX_PROCESSES];
    int i;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize allocation, max_need, and need arrays
    // (not shown here for brevity)

    // Create threads for processes
    for (i = 0; i < MAX_PROCESSES; i++) {
        process_ids[i] = i;
        pthread_create(&threads[i], NULL, processRequest, &process_ids[i]);
    }

    // Join threads
    for (i = 0; i < MAX_PROCESSES; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
