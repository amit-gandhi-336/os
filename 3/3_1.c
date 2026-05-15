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
    
    int s_fd, d_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    struct stat s_stat, d_stat;

    s_fd = open("3source.txt", O_RDONLY);
    d_fd = open("3backup.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while((bytes_read = read(s_fd, buffer, sizeof(buffer))) > 0){
        bytes_written = write(d_fd, buffer, bytes_read);
    }

    close(s_fd);
    close(d_fd);

    stat("3source.txt", &s_stat);
    stat("3backup.txt", &d_stat);

    if(s_stat.st_size == d_stat.st_size){
        printf("File Copied Successfully.\n");
        printf("Source Size: %ld bytes.\n", s_stat.st_size);
        printf("Backup Size: %ld bytes.\n", d_stat.st_size);
    }
    else{
        printf("Copy Failed.\n");
    }
    
    return 0;
}