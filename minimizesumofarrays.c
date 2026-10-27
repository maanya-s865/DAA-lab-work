
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void buildMaxHeap(int a[], int n) {
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

long long minimizeSum(int a[], int n, int k) {
    int i, temp;
    long long sum = 0;

    buildMaxHeap(a, n);

    for (i = 0; i < k; i++) {
        /* Largest element is at the root. */
        a[0] = (a[0] + 1) / 2;

        heapify(a, n, 0);
    }

    for (i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

int main() {
    static int a[MAX];
    int n, k, i;
    long long result;
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter number of operations K: ");
    scanf("%d", &k);

    if (k < 0) {
        printf("K cannot be negative.\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++)
        a[i] = 1 + rand() % 1000;

    start = clock();
    result = minimizeSum(a, n, k);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Minimum sum after %d operations = %lld\n", k, result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
