#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixMultiply(int A[][100], int B[][100], int C[][100], int n)
{
    int i, j, k;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for(k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int n, i, j;
    int A[100][100], B[100][100], C[100][100];

    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    if(n > 100)
    {
        printf("Please enter n <= 100.\n");
        return 0;
    }

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Clock 1
    start = clock();

    matrixMultiply(A, B, C, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}