#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double findMedian(int A[], int B[], int n)
{
    int low = 0;
    int high = n;
    int i, j;

    int maxLeftA, minRightA;
    int maxLeftB, minRightB;

    while(low <= high)
    {
        i = (low + high) / 2;
        j = n - i;

        if(i == 0)
            maxLeftA = -999999;
        else
            maxLeftA = A[i - 1];

        if(i == n)
            minRightA = 999999;
        else
            minRightA = A[i];

        if(j == 0)
            maxLeftB = -999999;
        else
            maxLeftB = B[j - 1];

        if(j == n)
            minRightB = 999999;
        else
            minRightB = B[j];

        if(maxLeftA <= minRightB &&
           maxLeftB <= minRightA)
        {
            if((2 * n) % 2 == 0)
            {
                int leftMax;

                if(maxLeftA > maxLeftB)
                    leftMax = maxLeftA;
                else
                    leftMax = maxLeftB;

                int rightMin;

                if(minRightA < minRightB)
                    rightMin = minRightA;
                else
                    rightMin = minRightB;

                return (leftMax + rightMin) / 2.0;
            }
        }
        else if(maxLeftA > minRightB)
        {
            high = i - 1;
        }
        else
        {
            low = i + 1;
        }
    }

    return -1;
}

int main()
{
    int n, i;
    int A[50000], B[50000];

    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    if(n > 50000)
    {
        printf("Maximum n is 50000.\n");
        return 0;
    }

    /*
       Generate two sorted arrays.
       Since we are interested in timing the
       median algorithm, generation is outside
       the clock.
    */

    for(i = 0; i < n; i++)
    {
        A[i] = 2 * i + 1;
        B[i] = 2 * i + 2;
    }

    // Clock 1
    start = clock();

    double median = findMedian(A, B, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Median = %f\n", median);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}