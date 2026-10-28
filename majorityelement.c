#include <stdio.h>

int majorityElement(int a[], int n)
{
    int candidate = 0;
    int count = 0;
    int i;

    // Find candidate
    for(i = 0; i < n; i++)
    {
        if(count == 0)
        {
            candidate = a[i];
            count = 1;
        }
        else if(a[i] == candidate)
        {
            count++;
        }
        else
        {
            count--;
        }
    }

    // Verify candidate
    count = 0;

    for(i = 0; i < n; i++)
    {
        if(a[i] == candidate)
            count++;
    }

    if(count > n / 2)
        return candidate;

    return -1;
}

int main()
{
    int a[] = {2, 2, 1, 1, 1, 2, 2};
    int n = 7;

    int result = majorityElement(a, n);

    if(result != -1)
        printf("Majority element = %d", result);
    else
        printf("No majority element");

    return 0;
}