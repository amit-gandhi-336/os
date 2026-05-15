#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<semaphore.h>

char arr[3][10] = {"BBC", "CNN", "AajTak"};

void* likho(void* arg){
    int num = *(int*) arg;
    for(int i=1 ; i<=5 ; i++){
        printf("%s %d\n",arr[num],i);
        usleep(100000);
    }

    pthread_exit(NULL);
}

int main(){
    
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    int a=0,b=1,c=2;

    pthread_create(&thread1, NULL, likho, &a);
    pthread_create(&thread2, NULL, likho, &b);
    pthread_create(&thread3, NULL, likho, &c);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}