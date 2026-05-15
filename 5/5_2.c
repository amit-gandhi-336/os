#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int n;

void avgtime(int TAT[], int WT[]){
    float avgWT=0, avgTAT=0;
    for(int i=0 ; i<n ; i++){
        avgWT += WT[i];
        avgTAT += TAT[i];
    }
    avgWT /= (float) n;
    avgTAT /= (float) n;

    printf("\nAvg Waiting Time = %.2f\n",avgWT);
    printf("Avg Turn Around Time = %.2f\n",avgTAT);
}

void display(int PID[], int AT[], int BT[], int CT[], int TAT[], int WT[]){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0 ; i<n ; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",PID[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }
}

void PRIO(int PID[], int AT[], int BT[], int CT[], int TAT[], int WT[], int pr[]){
    int totaltime = 0;
    for(int i=0 ; i<n ; i++) totaltime += BT[i];
    int curr = 0;
    int over[5] = {0};

    printf("\n0-> ");
    while(curr < totaltime){
        int min = 0;
        while(over[min] && min<n) min++;
        for(int i=1 ; i<n ; i++) if(!(over[i]) && pr[i] < pr[min]) min = i;

        curr += BT[min];
        CT[min] = curr;
        TAT[min] = CT[min] - AT[min];
        WT[min] = TAT[min] - BT[min];

        printf("P%d -%d-> ",PID[min],curr);

        over[min] = 1;
    } // while.
    avgtime(TAT,WT);
    display(PID,AT,BT,CT,TAT,WT);
}

int main(){

    n = 5;

    int PID[5] = {1,2,3,4,5};
    int AT[5] = {0};
    int BT[5] = {4,3,5,1,2};
    int pr[5] = {2,1,3,1,4};
    int CT[5],TAT[5],WT[5];

    PRIO(PID,AT,BT,CT,TAT,WT,pr);

    return 0;
}