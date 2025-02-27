

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p_num, r_num;
    printf("Enter the number of processes: ");
    scanf("%d", &p_num);
    printf("Enter the number of resources: ");
    scanf("%d", &r_num);

    int Allocation[p_num][r_num];
    int Max[p_num][r_num];
    int Available[r_num]; // Changed from Available[1][r_num] to Available[r_num]
    int Need[p_num][r_num];
    int flag[p_num]; // Initialize flag array

    // Initialize flag array to 0
    for (int i = 0; i < p_num; i++)
    {
        flag[i] = 0;
    }

    printf("\nEnter the entries of allocation table\n");
    for (int i = 0; i < p_num; i++)
    {
        printf("Enter the allocation for process %d: ", i + 1);
        for (int j = 0; j < r_num; j++)
        {
            scanf("%d", &Allocation[i][j]);
        }
    }

    printf("\nEnter the entries of max table\n");
    for (int i = 0; i < p_num; i++)
    {
        printf("Enter the max for process %d: ", i + 1);
        for (int j = 0; j < r_num; j++)
        {
            scanf("%d", &Max[i][j]);
        }
    }

    printf("\nEnter the entries of available table\n");
    for (int j = 0; j < r_num; j++)
    {
        scanf("%d", &Available[j]);
    }

    printf("\nNeed Table:\n");
    for (int i = 0; i < p_num; i++)
    {
        for (int j = 0; j < r_num; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            printf("%d\t", Need[i][j]);
        }
        printf("\n");
    }

    int Request[r_num]; // Changed from Request[0][r_num] to Request[r_num]
    int request_num = 0;

    printf("\nFor which process do you want to make a request (1 to %d): ", p_num);
    scanf("%d", &request_num);

    printf("Enter entries of request for process %d:\n", request_num);
    for (int j = 0; j < r_num; j++)
    {
        scanf("%d", &Request[j]);
    }

    // Check if the request can be satisfied
    int count1 = 0;
    for (int j = 0; j < r_num; j++)
    {
        if (Need[request_num - 1][j] >= Request[j])
        {
            count1++;
        }
    }

    if (count1 == r_num)
    {
        int count2 = 0;
        for (int j = 0; j < r_num; j++)
        {
            if (Available[j] >= Request[j])
            {
                count2++;
            }
        }

        if (count2 == r_num)
        {
            for (int j = 0; j < r_num; j++)
            {
                Available[j] -= Request[j];
                Allocation[request_num - 1][j] += Request[j];
                Need[request_num - 1][j] -= Request[j];
            }
            printf("\nRequest granted.\n");
        }
        else
        {
            printf("\nRequest cannot be granted due to insufficient resources.\n");
        }
    }
    else
    {
        printf("\nRequest cannot be granted as it exceeds the need.\n");
    }

    // Print updated Need, Allocation, and Available tables
    printf("\nUpdated Need Table:\n");
    for (int i = 0; i < p_num; i++)
    {
        for (int j = 0; j < r_num; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            printf("%d\t", Need[i][j]);
        }
        printf("\n");
    }

    printf("\nUpdated Allocation Table:\n");
    for (int i = 0; i < p_num; i++)
    {
        for (int j = 0; j < r_num; j++)
        {
            printf("%d\t", Allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nUpdated Available Table:\n");
    for (int j = 0; j < r_num; j++)
    {
        printf("%d\t", Available[j]);
    }
    printf("\n");

    // Safe sequence determination
    printf("\nCurrent Available Table:\n");
    for (int k = 0; k < p_num; k++)
    {
        if (flag[k] != 1)
        {
            int count = 0;
            for (int j = 0; j < r_num; j++)
            {
                if (Need[k][j] <= Available[j])
                {
                    count++;
                }
            }
            if (count == r_num)
            {
                flag[k] = 1;
                for (int j = 0; j < r_num; j++)
                {
                    Available[j] += Allocation[k][j];
                }
                printf("Safe sequence id %d:\n", k + 1);
            }
        }
    }

    return 0;
}
