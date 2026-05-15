#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

sem_t mum,rr;
int rc = 0;

void* reader(void* arg){
    int rno = *(int*) arg;
    for(int i=1 ; i<=3 ; i++){
        sem_wait(&rr);
        rc = rc + 1;
        if(rc == 1) sem_wait(&mum);
        sem_post(&rr);
        
        printf("Reader reading (%d) (Iteration = %d).\n",rno,i);
        usleep(1000000);
        sem_wait(&rr);
        rc = rc - 1;
        if(rc == 0) sem_post(&mum);
        sem_post(&rr);
    }

    pthread_exit(NULL);
}

void* writer(void* arg){
    int wno = *(int*) arg;
    for(int i=1 ; i<=3 ; i++){
        sem_wait(&mum);
        printf("Writer writing (%d) (Iteration = %d).\n",wno,i);
        usleep(1000000);
        sem_post(&mum);
    }

    pthread_exit(NULL);
}

int main(){

    sem_init(&mum,0,1);
    sem_init(&rr,0,1);

    pthread_t reader1;
    pthread_t reader2;
    pthread_t writer1;

    int r1=1,r2=2,w1=1;

    pthread_create(&reader1,NULL,reader,&r1);
    pthread_create(&reader2,NULL,reader,&r2);
    pthread_create(&writer1,NULL,writer,&w1);

    pthread_join(reader1,NULL);
    pthread_join(reader2,NULL);
    pthread_join(writer1,NULL);

    sem_destroy(&mum);
    sem_destroy(&rr);

    return 0;
}