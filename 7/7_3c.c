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

    /* Open shared memory */

    shm_fd = shm_open("/game_score",
                      O_RDONLY,
                      0666);

    /* Map memory */

    score = (int *) mmap(0,
                         sizeof(int),
                         PROT_READ,
                         MAP_SHARED,
                         shm_fd,
                         0);

    /* Read score 3 times */

    for(int i = 0; i < 3; i++)
    {
        printf("Reader: Score = %d\n",
               *score);

        sleep(1);
    }

    /* Cleanup */

    munmap(score, sizeof(int));

    close(shm_fd);

    shm_unlink("/game_score");

    return 0;
}

gcc writer.c -o writer -lrt