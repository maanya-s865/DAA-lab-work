#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort012(int a[], int n)
{
    int low = 0, mid = 0, high = n - 1;
    int temp;

    while(mid <= high)
    {
        if(a[mid] == 0)
        {
            temp = a[low];
            a[low] = a[mid];
            a[mid] = temp;

            low++;
            mid++;
        }
        else if(a[mid] == 1)
        {
            mid++;
        }
        else
        {
            temp = a[mid];
            a[mid] = a[high];
            a[high] = temp;

            high--;
        }
    }
}

int main()
{
    int n, i;
    int a[50000];

    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    // Generate random array containing only 0, 1 and 2
    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 3;
    }

    // Clock 1
    start = clock();

    sort012(a, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}