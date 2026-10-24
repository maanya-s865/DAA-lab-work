#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long maximumProduct(int a[], int n)
{
    long long product = 1;
    int negativeCount = 0;
    int zeroCount = 0;
    int largestNegative = -1000000;
    int i;

    for(i = 0; i < n; i++)
    {
        if(a[i] > 0)
        {
            product *= a[i];
        }
        else if(a[i] < 0)
        {
            product *= a[i];
            negativeCount++;

            if(a[i] > largestNegative)
                largestNegative = a[i];
        }
        else
        {
            zeroCount++;
        }
    }

    if(negativeCount % 2 != 0)
    {
        product /= largestNegative;
    }

    if(negativeCount == 0 && product == 1)
    {
        if(zeroCount > 0)
            return 0;

        return a[0];
    }

    return product;
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
        a[i] = (rand() % 21) - 10;
    }

    // Clock 1
    start = clock();

    long long result = maximumProduct(a, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Maximum Product = %lld\n", result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}