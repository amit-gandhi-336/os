#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>

int main(){
    
    key_t key;
    int shmid;
    int* temp;

    sem_t *sem  = sem_open("7sem", O_CREAT, 0666, 1);

    key = ftok("second", 66);

    shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    temp = (int*) shmat(shmid, NULL, 0);

    *temp = 0;
    for(int i=0 ; i<10 ; i++){
        sem_wait(sem);

            *temp = *temp + 1;
            printf("Temp = %d.\n",*temp);
        
        sem_post(sem);
        
        usleep(2000000);
    }
    printf("Writer finished.\n");

    shmdt(temp);

    sem_close(sem);
    
    return 0;
}

gcc file.c -pthread -o output