#include <stdio.h>
#include <time.h>

long long fibonacci(int n)
{
    if(n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n;

    clock_t start, end;
    double time_taken;

    printf("Enter n (0 to 45): ");
    scanf("%d", &n);

    if(n < 0 || n > 45)
    {
        printf("Enter n between 0 and 45.\n");
        return 0;
    }

    // Clock 1
    start = clock();

    long long result = fibonacci(n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}