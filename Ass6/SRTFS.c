#include<stdio.h>
#include<stdlib.h>

int current;

struct Process{
    int arrival;
    int burst;
    int rem;
    int completionStatus;
    int processNo;
};

int com1(const void* a, const void* b){
    struct Process* p1 = (struct Process *)a;
    struct Process* p2 = (struct Process *)b;
    return p1->arrival - p2->arrival;
}

int com2(const void* a, const void* b){
    struct Process* p1 = (struct Process *)a;
    struct Process* p2 = (struct Process *)b;

    if(p1->completionStatus == 0 && p2->completionStatus == 0){
        if(p1->arrival <= current && p2->arrival <= current){
            if(p1->rem < p2->rem){
            return -1;
        } else if(p1->rem > p2->rem){
            return 1;
        } else {
            if(p1->arrival <= p2->arrival){
                return -1;
            } else {
                return 1;
            }
        }
        } else if(p1->arrival <= current){
            return -1;
        } else if(p2->arrival <= current){
            return 1;
        } else {
            return 0;
        }
    } else if(p1->completionStatus == 0){
        return -1;
    } else if(p2->completionStatus == 0){
        return 1;
    } else {
        return 0;
    }
}
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    struct Process processes[n];
    int arriv[n];
    for(int i = 0; i < n; i++){
        printf("Enter arrival time and burst time for process %d :", i);
        scanf("%d", &processes[i].arrival);
        scanf("%d", &processes[i].burst);
        processes[i].processNo = i;
        processes[i].rem = processes[i].burst;
        arriv[i] = processes[i].arrival;
    }
    qsort(arriv, n, sizeof(int), compare);

    int wt[n];
    int tat[n];
    int ct[n];
    int pNo[n];
    qsort(processes, n, sizeof(struct Process), com2);
    int total = 0;
    current = processes[0].arrival;
    while(total < n){
        qsort(processes, n, sizeof(struct Process), com2);
        int index = processes[0].processNo;
        int smallestRem = processes[0].rem;
        int nextsmall = processes[1].rem;
        if(nextsmall == 0) {
            current += smallestRem;
            total++;
            processes[0].completionStatus = 1;
            processes[0].rem = 0;
            ct[index] = current;
            tat[index] = current - processes[0].arrival;
            wt[index] = tat[index] - processes[0].burst;
        } else {
            int time = processes[0].rem;
            for(int i = 0; i < n; i++){
                if(arriv[i] > current){
                    time = arriv[i];
                    break;
                }
            }
            if(time >= current + processes[0].rem){
                current += smallestRem;
                total++;
                processes[0].rem  = 0;
                processes[0].completionStatus = 1;
                ct[index] = current;
                tat[index] = current - processes[0].arrival;
                wt[index] = tat[index] - processes[0].burst;
            } else {
                processes[0].rem -= (time - current);
                current = time;
            }
        }
    }
    for(int i = 0; i < n; i++){
        printf("\nprocess %d, tat: %d, ct: %d, wt: %d", i, tat[i], ct[i], wt[i]);
    }
    return 0;
}