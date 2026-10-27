
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define RANGE 1000

void countingSort(int a[], int n) {
    int count[RANGE] = {0};
    int i, j = 0;

    for (i = 0; i < n; i++)
        count[a[i]]++;

    for (i = 0; i < RANGE; i++) {
        while (count[i] > 0) {
            a[j++] = i;
            count[i]--;
        }
    }
}

int main() {
    static int a[MAX];
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
        a[i] = rand() % RANGE;

    start = clock();
    countingSort(a, n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution Time = %f seconds\n", time_taken);

    printf("First 10 sorted elements: ");
    for (i = 0; i < n && i < 10; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
