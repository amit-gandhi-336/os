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
// cd /mnt/c
// cd Users/Sarang/Desktop/CODES/SEM-4/OS/Practice

int main(){
    int id;
    char buffer[1024];
    ssize_t fd;

    pid_t pid = fork();
    if(pid == 0){
        fd = open("3232caca.txt", O_WRONLY | O_CREAT | O_TRUNC | 0644);

        write(fd, "Child lihito.\n", 15);
        
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        close(fd);
    }
    else{
        fd = open("3232caca.txt", O_WRONLY | O_CREAT | O_TRUNC | 0644);

        write(fd, "Parent lihito.\n", 16);

        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent Parent PID: %d\n", getppid());
        
        close(fd);
    }

}