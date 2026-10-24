
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int i;

    // Build a max heap
    for(i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Move the largest element to the end
    for(i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
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

    if(n < 1 || n > 50000)
    {
        printf("Enter n between 1 and 50000.\n");
        return 0;
    }

    srand((unsigned)time(NULL));

    for(i = 0; i < n; i++)
        a[i] = rand() % 100000;

    // Clock 1
    start = clock();

    heapSort(a, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sorted array (first 10 elements or fewer):\n");

    for(i = 0; i < n && i < 10; i++)
        printf("%d ", a[i]);

    printf("\nExecution Time = %f seconds\n", time_taken);

    return 0;
}
