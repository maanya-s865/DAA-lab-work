#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 128

void addMatrix(int A[MAX][MAX], int B[MAX][MAX],
               int C[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int A[MAX][MAX], int B[MAX][MAX],
                    int C[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX], int n)
{
    int i, j;
    int k;
    int newSize;

    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];

    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];

    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX];
    int M4[MAX][MAX], M5[MAX][MAX], M6[MAX][MAX];
    int M7[MAX][MAX];

    int T1[MAX][MAX], T2[MAX][MAX];

    if(n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    newSize = n / 2;

    for(i = 0; i < newSize; i++)
    {
        for(j = 0; j < newSize; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    addMatrix(A11, A22, T1, newSize);
    addMatrix(B11, B22, T2, newSize);
    strassen(T1, T2, M1, newSize);

    addMatrix(A21, A22, T1, newSize);
    strassen(T1, B11, M2, newSize);

    subtractMatrix(B12, B22, T2, newSize);
    strassen(A11, T2, M3, newSize);

    subtractMatrix(B21, B11, T2, newSize);
    strassen(A22, T2, M4, newSize);

    addMatrix(A11, A12, T1, newSize);
    strassen(T1, B22, M5, newSize);

    subtractMatrix(A21, A11, T1, newSize);
    addMatrix(B11, B12, T2, newSize);
    strassen(T1, T2, M6, newSize);

    subtractMatrix(A12, A22, T1, newSize);
    addMatrix(B21, B22, T2, newSize);
    strassen(T1, T2, M7, newSize);

    for(i = 0; i < newSize; i++)
    {
        for(j = 0; j < newSize; j++)
        {
            C[i][j] =
                M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

            C[i][j + newSize] =
                M3[i][j] + M5[i][j];

            C[i + newSize][j] =
                M2[i][j] + M4[i][j];

            C[i + newSize][j + newSize] =
                M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}

int main()
{
    int n, i, j;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    clock_t start, end;
    double time_taken;

    printf("Enter n (power of 2): ");
    scanf("%d", &n);

    if(n > MAX || n < 2)
    {
        printf("Enter n between 2 and %d.\n", MAX);
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

    strassen(A, B, C, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}