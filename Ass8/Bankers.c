#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

struct Process{
    int status;
    int maxm[3];
    int curr[3];
    int need[3];
    int pNo;
};

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    struct Process processes[n];
    int a, b, c;
    printf("Enter available of a, b, c: ");
        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);

    for(int i = 0; i < n; i++){
        printf("Max a,b,c for process %d: ", i);
        scanf("%d", &processes[i].maxm[0]);
        scanf("%d", &processes[i].maxm[1]);
        scanf("%d", &processes[i].maxm[2]);

        printf("current a,b,c for process %d: ", i);
        scanf("%d", &processes[i].curr[0]);
        scanf("%d", &processes[i].curr[1]);
        scanf("%d", &processes[i].curr[2]);

        for(int j = 0; j < 3; j++){
            processes[i].need[j] = processes[i].maxm[j] - processes[i].curr[j];
        }

        processes[i].status = 0;
        processes[i].pNo = i;
    }

    int total = 0;
    int ans[n];
    while(total < n){
        int find = 0;
        int index;
        int fa, fb, fc;
        for(int i = 0; i < n; i++){
            fa = processes[i].need[0];
            fb = processes[i].need[1];
            fc = processes[i].need[2];
            if(processes[i].status == 0 && fa <= a && fb <= b && fc <= c){
                find = 1;
                index = i;
                break;
            }
        }
        if(find == 0 && total < n){
            printf("No safe state");
            return 0;
        }else {
            ans[total] = processes[index].pNo;
            total++;
            a += processes[index].curr[0];
            b += processes[index].curr[1];
            c += processes[index].curr[2];
            processes[index].status = 1;
        }
    }

    printf("safe states: ");
    for(int i = 0; i < n; i++){
        printf("%d", ans[i]);
    }

    return 0;
}