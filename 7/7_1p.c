#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(){

    key_t key;
    int shmid;
    float *temp;

    key = ftok("random", 65);

    shmid = shmget(key, sizeof(float) * 5, 0666 | IPC_CREAT);

    temp = (float *) shmat(shmid, NULL, 0);

    printf("Enter 5 temperature values:\n");
    for(int i=0 ; i<5 ; i++){
        printf("Temperature %d: ", i+1);
        scanf("%f", &temp[i]);
    }
    printf("\nTemperature values written to shared memory.\n");

    shmdt(temp);

    return 0;
}