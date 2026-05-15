#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<semaphore.h>

int mycounter = 0;

pthread_mutex_t lock;

void* incre(void* arg){
    for(int i=0 ; i<5000 ; i++){
        pthread_mutex_lock(&lock);

        int temp = mycounter;
        temp++;
        usleep(1);
        mycounter = temp;

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main(){

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, incre, NULL);
    pthread_create(&thread2, NULL, incre, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Finally mycounter = %d\n",mycounter);

    pthread_mutex_destroy(&lock);

    return 0;
}

gcc file.c -pthread -o output