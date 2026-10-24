#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low;
    int j;

    for(j = low; j < high; j++)
    {
        if(a[j] < pivot)
        {
            swap(&a[i], &a[j]);
            i++;
        }
    }

    swap(&a[i], &a[high]);

    return i;
}

int quickSelect(int a[], int low, int high, int k)
{
    int pivotIndex;

    if(low == high)
        return a[low];

    pivotIndex = partition(a, low, high);

    if(k == pivotIndex)
        return a[k];

    else if(k < pivotIndex)
        return quickSelect(a, low, pivotIndex - 1, k);

    else
        return quickSelect(a, pivotIndex + 1, high, k);
}

int main()
{
    int n, k, i;
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

    printf("Enter k (1 to %d): ", n);
    scanf("%d", &k);

    if(k < 1 || k > n)
    {
        printf("Invalid k value.\n");
        return 0;
    }

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 100000;
    }

    // kth largest corresponds to index n-k
    // in ascending-order selection

    // Clock 1
    start = clock();

    int result = quickSelect(a, 0, n - 1, n - k);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Kth Largest Element = %d\n", result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}