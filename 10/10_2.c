#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(){
    
    int base[3] = {1000,2000,3000};
    int limit[3] = {400,500,300};

    int req[3][2] = {{0,200}, {1,600}, {2,150}};

    for(int i=0 ; i<3 ; i++){
        int id = req[i][0];
        if(id >= 3 || id < 0){
            printf("Segmentation Fault.\n");
            printf("Invalid Segment Number.\n\n");
            continue;
        }

        if(req[i][1] > limit[id]){
            printf("Segmentation Fault.\n");
            printf("Need %d which is more than %d.\n\n",req[i][1], limit[id]);
        }
        else{
            int phys = base[id] + req[i][1];
            printf("Physcial Address = %d.\n\n",phys);
        }
    }

    return 0;
}