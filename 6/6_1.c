#include <stdio.h>

int main()
{
    int allocation[4][2] =
    {
        {1,1},
        {1,0},
        {1,1},
        {0,1}
    };

    int max[4][2] =
    {
        {2,2},
        {2,1},
        {3,2},
        {1,2}
    };

    int available[2] = {1,1};

    int need[4][2];

    int finish[4] = {0};

    int safeSeq[4];

    int work[2];

    int count = 0;

    /* Calculate Need */

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            need[i][j] =
                max[i][j] -
                allocation[i][j];
        }
    }

    /* Copy available into work */

    for(int j = 0; j < 2; j++)
    {
        work[j] = available[j];
    }

    /* Safety Algorithm */

    while(count < 4)
    {
        int found = 0;

        for(int i = 0; i < 4; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(int j = 0; j < 2; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSeq[count++] = i;

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

        /* No process can proceed */

        if(found == 0)
        {
            printf("System is in deadlock\n");

            return 0;
        }
    }

    printf("Safe sequence: ");

    for(int i = 0; i < 4; i++)
    {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}