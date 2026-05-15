#include <stdio.h>

int main()
{
    int allocation[4][3] =
    {
        {1,1,0},
        {1,2,1},
        {1,0,2},
        {0,1,1}
    };

    int max[4][3] =
    {
        {3,2,2},
        {2,3,3},
        {3,1,4},
        {1,2,2}
    };

    int available[3] = {2,1,2};

    int need[4][3];

    int request[3] = {1,0,2};

    int finish[4] = {0};

    int safeSeq[4];

    int work[3];

    int count = 0;

    /* Calculate Need */

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            need[i][j] =
                max[i][j] -
                allocation[i][j];
        }
    }

    /* Check Request <= Need and Available */

    for(int j = 0; j < 3; j++)
    {
        if(request[j] > need[2][j] ||
           request[j] > available[j])
        {
            printf("Request denied\n");
            return 0;
        }
    }

    /* Pretend allocation */

    for(int j = 0; j < 3; j++)
    {
        available[j] -= request[j];

        allocation[2][j] += request[j];

        need[2][j] -= request[j];
    }

    /* Copy available into work */

    for(int j = 0; j < 3; j++)
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

                for(int j = 0; j < 3; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSeq[count++] = i;

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            printf("Request denied\n");

            return 0;
        }
    }

    printf("Request granted\n");

    printf("Safe Sequence: ");

    for(int i = 0; i < 4; i++)
    {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}