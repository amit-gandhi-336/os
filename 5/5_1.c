#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

int n;

void avgTAT(int WT[]){
    float avg = 0;
    for(int i=0 ; i<n ; i++) avg += WT[i];
    avg /= (float) n;

    printf("\nAvg Waiting Time: %.2f\n",avg);
}

void display(int PID[], int AT[], int BT[], int CT[], int TAT[], int WT[]){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0 ; i<n ; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",PID[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }
}

void FCFS(int PID[], int AT[], int BT[], int CT[], int TAT[], int WT[]){
    int total = 0;
    for(int i=0 ; i<n ; i++) total += BT[i];
    int curr = 0;
    int over[5] = {0};

    printf("Gantt chart:\n0-> ");
    while(curr < total){
        for(int i=0 ; i<n ; i++){
            // Process arrived condition.
            if(!(over[i]) && AT[i] <= curr){
                curr += BT[i];
                CT[i] = curr;
                TAT[i] = CT[i] - AT[i];
                WT[i] = TAT[i] - BT[i];

                printf("P%d -%d-> ",PID[i], curr);
                
                over[i] = 1;
            } // if.
        } // for.
    } // while.
    display(PID,AT,BT,CT,TAT,WT);
    avgTAT(TAT);
}

int main(){

    n = 5;
    int PID[5] = {1,2,3,4,5};
    int AT[5] = {0,1,2,3,4};
    int BT[5] = {6,4,2,3,1};
    int CT[n], TAT[n], WT[n];

    FCFS(PID, AT, BT, CT, TAT, WT);

    return 0;
}