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
    int i = low - 1;
    int j;

    for(j = low; j < high; j++)
    {
        if(a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

int randomizedPartition(int a[], int low, int high)
{
    int randomIndex;

    randomIndex = low + rand() % (high - low + 1);

    swap(&a[randomIndex], &a[high]);

    return partition(a, low, high);
}

void randomizedQuickSort(int a[], int low, int high)
{
    int pivotIndex;

    if(low < high)
    {
        pivotIndex = randomizedPartition(a, low, high);

        randomizedQuickSort(a, low, pivotIndex - 1);

        randomizedQuickSort(a, pivotIndex + 1, high);
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

    if(n > 50000)
    {
        printf("Maximum n is 50000.\n");
        return 0;
    }

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 100000;
    }

    // Clock 1
    start = clock();

    randomizedQuickSort(a, 0, n - 1);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}