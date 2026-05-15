#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<ctype.h>
#include<string.h>
// cd /mnt/c
// cd Users/Sarang/Desktop/CODES/SEM-4/OS/Practice

int main(){

    int fd[2];
    pid_t pid;
    char message[] = "Hello from Parent";
    char buffer[1024];
    int i;

    pipe(fd);

    pid = fork();
    if(pid == 0){
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        for(int i=0 ; buffer[i] != '\0' ; i++){
            buffer[i] = toupper(buffer[i]);
        }

        printf("Child received in uppercase: %s\n",buffer);

        close(fd[0]);
    }
    else{
        close(fd[0]);

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);
    }

    return 0;
}