#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int n, q;

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

void RR(int PID[], int AT[], int BT[], int CT[], int TAT[], int WT[]){
    int totaltime = 0;
    for(int i=0 ; i<n ; i++) totaltime += BT[i];
    int over[4] = {0};
    int curr = 0;
    int RM[4]; // Remaining time.
    for(int i=0 ; i<n ; i++) RM[i] = BT[i]; // Initially, RM = BT.

    printf("0-> ");
    while(curr < totaltime){
        for(int i=0 ; i<n ; i++){
            if(!(over[i])){
                // Remaining time more than time quantum.
                if(RM[i] > q){
                    curr += q;
                    RM[i] -= q;
                }
                
                // Remaining time less than or equal to time quantum.
                else{
                    curr += RM[i];
                    RM[i] = 0;

                    CT[i] = curr;
                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];

                    over[i] = 1;
                }

                printf("J%d -%d-> ",PID[i], curr);
            } // if.
        } // for.
    } // while.
    avgtime(TAT,WT);
    display(PID,AT,BT,CT,TAT,WT);
}

int main(){

    n = 4;
    q = 3;

    int PID[4] = {1,2,3,4};
    int AT[4] = {0};
    int BT[4] = {10,4,6,3};
    int CT[4],TAT[4],WT[4];

    RR(PID,AT,BT,CT,TAT,WT);

    return 0;
}