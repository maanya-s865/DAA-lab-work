#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int smallestMissingPositive(int a[], int n)
{
    int i, index, temp;

    for(i = 0; i < n; i++)
    {
        while(a[i] > 0 &&
              a[i] <= n &&
              a[a[i] - 1] != a[i])
        {
            index = a[i] - 1;

            temp = a[i];
            a[i] = a[index];
            a[index] = temp;
        }
    }

    for(i = 0; i < n; i++)
    {
        if(a[i] != i + 1)
            return i + 1;
    }

    return n + 1;
}

int main()
{
    int n, i;
    int a[50000];

    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    if(n < 1 || n > 50000)
    {
        printf("Enter n between 1 and 50000.\n");
        return 0;
    }

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        a[i] = (rand() % (2 * n + 1)) - n;
    }

    // Clock 1
    start = clock();

    int result = smallestMissingPositive(a, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Smallest Missing Positive = %d\n", result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}