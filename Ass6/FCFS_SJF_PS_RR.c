#include<stdio.h>
#include<stdlib.h>

int cTime;  //to track the completion time
int total;
int priority[100];


int vector[1000];
int start;
int end;
int now;
int remEt[1000];


struct Process{
    int completionStatus;
    int arrival;
    int burst;
    int processNo;
};


int compareArrival(const void *a, const void *b){
    struct Process* p1 = (struct Process *)a;
    struct Process* p2 = (struct Process *)b;

    return p1->arrival - p2->arrival;
}

void fcfs(struct Process processes[], int n){
    qsort(processes, n, sizeof(struct Process), compareArrival);

    int waiting[n];
    int turnaround[n];
    int completion[n];
    completion[0] = processes[0].arrival + processes[0].burst;
    waiting[0] = 0;
    turnaround[0] = processes[0].burst;
    for(int i = 1; i < n; i++){
        if(processes[i].arrival <= completion[i-1]){
            waiting[i] = completion[i-1] - processes[i].arrival;
            turnaround[i] = waiting[i] + processes[i].burst;
            completion[i] = completion[i-1] + processes[i].burst;
        } else {
            waiting[i] = 0;
            completion[i] = processes[i].arrival + processes[i].burst;
            turnaround[i] = processes[i].burst;
        }
    }
        for(int i = 0; i < n; i++){
            printf("\n for process %d, WT: %d, CT: %d, TAT:%d", i, waiting[i], completion[i], turnaround[i]);
        }
}

int compare2(const void* a, const void* b){
    struct Process* p1 = (struct Process *) a;
    struct Process* p2 = (struct Process *) b;
    if(p1->completionStatus == 0 && p2->completionStatus == 0){
        if(p1->arrival <= cTime && p2 -> arrival <= cTime){
            if(p1->burst <= p2->burst){
                return -1;
            } else {
                return 1;
            }
        } else if(p1->arrival <= cTime && p2 -> arrival > cTime){
            return -1;
        } else if(p1->arrival > cTime && p2 -> arrival <= cTime){
            return 1;
        } else {
            return 0;
        }
    } else if(p1->completionStatus != 0 && p2->completionStatus == 0){
        return 1;
    } else if(p1->completionStatus == 0 && p2->completionStatus != 0){
        return -1;
    } else {
        return 0;
    }
    
}

void SJF(struct Process processes[], int n){
    qsort(processes, n, sizeof(struct Process), compare2);
    int waiting[n];
    int tat[n];
    int ct[n];
    int pNo[n];
    pNo[0] = 0;
    waiting[0] = 0;
    tat[0] = processes[0].burst;
    ct[0] = processes[0].arrival + processes[0].burst;
    cTime = ct[0];
    processes[0].completionStatus = 1; //complete
    for(int i = 1; i < n; i++){
        qsort(processes, n, sizeof(struct Process), compare2);
        if(processes[0].arrival >= ct[i-1]){
            pNo[i] = processes[0].processNo;
            waiting[i] = 0;
            tat[i] = processes[0].burst;
            ct[i] = processes[0].arrival + processes[0].burst;
            cTime = ct[i];
            processes[0].completionStatus = 1; //done this also
        } else {
            pNo[i] = processes[0].processNo;
            waiting[i] = ct[i-1] - processes[0].arrival;
            tat[i] = waiting[i] + processes[0].burst;
            ct[i] = ct[i-1] + processes[0].burst;
            cTime = ct[i];
            processes[0].completionStatus = 1; //completed
        }
    }

    for(int i = 0; i < n; i++){
         printf("\n for process %d, WT: %d, CT: %d, TAT:%d", pNo[i], waiting[i], ct[i], tat[i]);
    }
}

int compare3(const void* a, const void* b){
    struct Process* p1 = (struct Process *)a;
    struct Process* p2 = (struct Process *)b;

    if(p1->completionStatus == 0 && p2->completionStatus == 0){
        if(p1->arrival <= cTime && p2 -> arrival <= cTime){
            int z1, z2;
            for(int i = 0; i < total; i++){
                if(priority[i]-1 == p1 -> processNo) z1 = i;
                if(priority[i]-1 == p2->processNo) z2 = i;
            }
            if(z1 <= z2){
                return -1;
            } else {
                return 1;
            }
        } else if(p1-> arrival <= cTime){
            return -1;
        } else if(p2-> arrival <= cTime){
            return 1;
        } else {
            return 0;
        }
    } else if(p1 -> completionStatus == 0){
        return -1;
    } else if(p2 ->completionStatus == 0){
        return 1;
    }else {
        return 0;
    }
    return -11;
}

void PS(struct Process processes[], int n){
    printf("Enter the prioority order: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &priority[i]);
    }
    printf("\n");

    int wt[n];
    int tat[n];
    int ct[n];
    int pNo[n];
    qsort(processes, n, sizeof(struct Process), compareArrival);
    cTime = processes[0].arrival;
    qsort(processes, n, sizeof(struct Process), compare3);
    wt[0] = 0;
    tat[0] = processes[0].burst;
    ct[0] = processes[0].arrival + processes[0].burst;
    pNo[0] = processes[0].processNo;
    processes[0].completionStatus = 1;
    for(int i = 1; i < n; i++){
        qsort(processes, n, sizeof(struct Process), compare3);
        if(processes[0].arrival >= ct[i-1]){
            wt[i] = 0;
            tat[i] = processes[0].burst;
            ct[i] = processes[0].arrival + processes[0].burst;
            pNo[i] = processes[0].processNo;
            processes[0].completionStatus = 1;
        } else {
            wt[i] = ct[i-1] - processes[0].arrival;
            tat[i] = wt[i] + processes[0].burst;
            ct[i] = ct[i-1] + processes[0].burst;
            pNo[i] = processes[0].processNo;
            processes[0].completionStatus = 1;
        }
    }


    for(int i = 0; i < n; i++){
        printf("\nfor process %d, wt: %d, tat: %d, ct: %d", pNo[i], wt[i], tat[i], ct[i]);
    }
}

int compare4(const void* a, const void* b){
    struct Process* p1 = (struct Process *)a;
    struct Process* p2 = (struct Process *)b;
    if(p1->completionStatus == 0 && p2 ->completionStatus == 0){
        if(p1->arrival <= now && p2->arrival <= now){
            if(remEt[p1->processNo] > 0 && remEt[p2->processNo > 0]){
                int z1, z2;
                for(int i = start; i <= end; i++){
                    if(vector[i] == p1->processNo) z1 = i;
                    if(vector[i] == p2->processNo) z2 = i;
                }
                if(z1 <= z2) return -1;
                else return 1;
            } else if(remEt[p1-> processNo] > 0){
                return -1;
            } else if(remEt[p2-> processNo] > 0){
                return 1;
            } else {
                return 0;
            }
        } else if(p1->arrival <= now){
            return 0;
        } else if(p2->arrival <= now){
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

    return -11;

}

void RR(struct Process processes[], int n){
    int wt[n];
    int tat[n];
    int ct[n];
    int all = 0;
    for(int i = 0; i < n; i++){
        remEt[i] = processes[i].burst;
    }
    qsort(processes, n, sizeof(struct Process), compareArrival);
    start = 0;
    end = 0;
    int i = 0;
    while(i < n){
        vector[end] = processes[i].processNo;
        end++;
        i++;
    }
    while(all < n){
        qsort(processes, n, sizeof(struct Process), compare4);
        int current = processes[0].processNo;
        if(remEt[current] <= 2){
            remEt[current] = 0;
            processes[0].completionStatus = 1;
            all++;
            now += remEt[current];
            ct[current] = now;
            wt[current] = ct[current] - processes[0].arrival;
            vector[end] = current;
            end++;
            start--;
        } else {
            vector[end] = current;
            end++;
            start--;
            remEt[current] -= 2;
            now += 2;
        }
    }

    for(int i = 0; i < n; i++){
        printf("\nfor process %d wt: %d, tat: %d, ct: %d", i, wt[i], tat[i], ct[i]);
    }

}




int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    total = n;
    struct Process processes[n];
    for(int i = 0; i < n; i++){
        printf("Enter the arrival and burst time of process %d: ", i);
        scanf("%d", &processes[i].arrival);
        scanf("%d", &processes[i].burst);
        processes[i].processNo = i+1;
        processes[i].completionStatus = 0;
    }
    
    // fcfs(processes, n);
    // SJF(processes, n);
    // PS(processes, n);
    RR(processes, n);
    

}