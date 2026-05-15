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

#define PAGESIZE 4096

int main(){
    int vir = 0x00403004;

    int l1_index = (vir >> 22) & 0x3FF;
    int l2_index = (vir >> 12) & 0x3FF;
    int offset = (vir >> 0) & 0xFFF;

    int l1_table[1024] = {0};
    l1_table[1] = 5000;

    int l2_table[1024] = {0};
    l2_table[3] = 7;

    int l2_base = l1_table[1];
    int frame = l2_table[3];

    int phys = (frame * PAGESIZE) + offset;

    printf("Virtual Address = 0x%X\n",vir);
    printf("L1 index = %d\n",l1_index);
    printf("L2 index = %d\n",l2_index);
    printf("Offset = %d\n",offset);
    printf("L2 base = %d\n",l2_base);
    printf("Frame = %d\n",frame);
    printf("Physical Address = %d (0x%X)\n",phys,phys);

    return 0;
}