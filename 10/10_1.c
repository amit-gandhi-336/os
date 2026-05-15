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

#define PAGE 4096

int main(){
    int page_table[] = {3,1,4};

    int virtual_addresses[] = {0x1A3F, 0x2B10};

    int n = sizeof(virtual_addresses) / sizeof(virtual_addresses[0]);

    for(int i=0 ; i<n ; i++){
        int vir = virtual_addresses[i];

        int pgno = vir / PAGE;
        int offset = vir % PAGE;

        if(pgno >= 3){
            printf("Virtual Address: 0x%X -> Invalid.\n", vir);
            continue;
        }

        int frame = page_table[pgno];

        int phys= (frame * PAGE) + offset;

        printf("\nVirtual Address : 0x%X\n", vir);
        printf("Page Number     : %d\n", pgno);
        printf("Offset          : 0x%X\n", offset);
        printf("Frame Number    : %d\n", frame);
        printf("Physical Address: 0x%X\n", phys);
    }

    return 0;
}