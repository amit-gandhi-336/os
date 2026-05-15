#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/types.h>

#define MAX 100
int arr[MAX];
int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

// Thread 1.
void* first(void* arg){
    for(int i=0 ; i<25 ; i++){
        sum1 += arr[i];
    }
    printf("Thread 1 Sum = %d\n",sum1);

    pthread_exit(NULL);
}

// Thread 2.
void* second(void* arg){
    for(int i=25 ; i<50 ; i++){
        sum2 += arr[i];
    }
    printf("Thread 2 Sum = %d\n",sum2);

    pthread_exit(NULL);
}

// Thread 3.
void* third(void* arg){
    for(int i=50 ; i<75 ; i++){
        sum3 += arr[i];
    }
    printf("Thread 3 Sum = %d\n",sum3);

    pthread_exit(NULL);
}

// Thread 4.
void* fourth(void* arg){
    for(int i=75 ; i<MAX ; i++){
        sum4 += arr[i];
    }
    printf("Thread 4 Sum = %d\n",sum4);

    pthread_exit(NULL);
}

int main(){

    for(int i=0 ; i<MAX ; i++){
        arr[i] = i+1;
    }

    // thread.
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    // Create thread.
    pthread_create(&thread1, NULL, first, NULL);
    pthread_create(&thread2, NULL, second, NULL);
    pthread_create(&thread3, NULL, third, NULL);
    pthread_create(&thread4, NULL, fourth, NULL);

    // Join thread.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    int total = sum1 + sum2 + sum3 + sum4;
    printf("\nTotal sum = %d\n",total);

    return 0;
}