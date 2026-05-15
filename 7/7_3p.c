#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int shm_fd;

    int *score;

    /* Create shared memory */

    shm_fd = shm_open("/game_score",
                      O_CREAT | O_RDWR,
                      0666);

    /* Set size */

    ftruncate(shm_fd, sizeof(int));

    /* Map shared memory */

    score = (int *) mmap(0,
                         sizeof(int),
                         PROT_WRITE,
                         MAP_SHARED,
                         shm_fd,
                         0);

    /* Update score */

    *score = 100;

    printf("Writer: Score = %d\n",
           *score);

    sleep(1);

    *score = 200;

    printf("Writer: Score = %d\n",
           *score);

    sleep(1);

    *score = 300;

    printf("Writer: Score = %d\n",
           *score);

    sleep(1);

    /* Cleanup */

    munmap(score, sizeof(int));

    close(shm_fd);

    return 0;
}

gcc writer.c -o writer -lrt