
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000

void insertionSort(float a[], int n) {
    int i, j;
    float key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

void bucketSort(float a[], int n) {
    static float buckets[MAX];
    static int count[MAX];
    int start[MAX], i, j, b, pos = 0;

    for (i = 0; i < n; i++) {
        b = (int)(a[i] * n);
        if (b >= n) b = n - 1;
        count[b]++;
    }

    start[0] = 0;
    for (i = 1; i < n; i++)
        start[i] = start[i - 1] + count[i - 1];

    int next[MAX];
    for (i = 0; i < n; i++)
        next[i] = start[i];

    for (i = 0; i < n; i++) {
        b = (int)(a[i] * n);
        if (b >= n) b = n - 1;
        buckets[next[b]++] = a[i];
    }

    for (i = 0; i < n; i++) {
        insertionSort(buckets + start[i], count[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < count[i]; j++)
            a[pos++] = buckets[start[i] + j];
    }
}

int main() {
    static float a[MAX];
    int n, i;
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid size!\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    for (i = 0; i < n; i++)
        a[i] = (float)rand() / ((float)RAND_MAX + 1.0f);

    start = clock();
    bucketSort(a, n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    printf("First 10 sorted elements: ");
    for (i = 0; i < n && i < 10; i++)
        printf("%.3f ", a[i]);

    printf("\n");
    return 0;
}
