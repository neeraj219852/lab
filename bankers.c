#include <stdio.h>

void main() {
    int i, j, n, m, alloc[50][50], max[50][50], need[50][50], avail[50], work[50], finish[50], ind = 0, flag, found, ss[50];

    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    printf("Enter the number of resources:\n");
    scanf("%d", &m);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available matrix:\n");
    for (j = 0; j < m; j++) 
    {  // Fixed iteration over resources instead of processes
        scanf("%d", &avail[j]);
    }

    // Calculate the Need Matrix
    for (i = 0; i < n; i++)
     {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("The Need matrix is:\n");
    for (i = 0; i < n; i++)
     {
        for (j = 0; j < m; j++) 
        {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    // Initialize Work and Finish arrays
    for (j = 0; j < m; j++) 
    {
        work[j] = avail[j];
    }

    for (i = 0; i < n; i++) 
    {
        finish[i] = 0;
    }

    int count = 0;//bankers
    while (count < n) 
    {
        found = 0;
        for (i = 0; i < n; i++) 
        {
            if (finish[i] == 0) 
            {
                flag = 0;
                for (j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) 
                {
                    for (j = 0; j < m; j++) 
                    {
                        work[j] += alloc[i][j];
                    }
                    found = 1;
                    finish[i] = 1;
                    count++;
                    ss[ind++] = i;
                }
            }
        }
        if (found == 0) 
        {
            printf("The system is not safe.\n");
            return;
        }
    }

    printf("The safe sequence is:\n");
    for (i = 0; i < n; i++) 
    {
        printf("P%d\t", ss[i]);
    }
}
