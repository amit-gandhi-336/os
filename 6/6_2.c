#include <stdio.h>

int main()
{
    int allocation[3][2] =
    {
        {1,0},
        {0,1},
        {1,1}
    };

    int request[3][2] =
    {
        {0,1},
        {1,0},
        {1,1}
    };

    int available[2] = {0,0};

    int finish[3] = {0};

    int work[2];

    /* Copy available into work */

    for(int j = 0; j < 2; j++)
    {
        work[j] = available[j];
    }

    int found;

    do
    {
        found = 0;

        for(int i = 0; i < 3; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(int j = 0; j < 2; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                /* Process can finish */

                if(possible)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

    } while(found);

    /* Check deadlock */

    int deadlock = 0;

    for(int i = 0; i < 3; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            break;
        }
    }

    if(deadlock)
    {
        printf("Deadlock detected\n");

        printf("Processes involved: ");

        for(int i = 0; i < 3; i++)
        {
            if(finish[i] == 0)
            {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }
    else
    {
        printf("No deadlock detected\n");
    }

    return 0;
}