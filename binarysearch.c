#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int canAllocate(int pages[], int n, int students, int maxPages)
{
    int studentsUsed = 1;
    int currentPages = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        if(pages[i] > maxPages)
            return 0;

        if(currentPages + pages[i] <= maxPages)
        {
            currentPages += pages[i];
        }
        else
        {
            studentsUsed++;
            currentPages = pages[i];

            if(studentsUsed > students)
                return 0;
        }
    }

    return 1;
}

int minimumPages(int pages[], int n, int students)
{
    int low = 0;
    int high = 0;
    int mid;
    int answer = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        if(pages[i] > low)
            low = pages[i];

        high += pages[i];
    }

    while(low <= high)
    {
        mid = low + (high - low) / 2;

        if(canAllocate(pages, n, students, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return answer;
}

int main()
{
    int n, students, i;
    int pages[50000];

    clock_t start, end;
    double time_taken;

    printf("Enter number of books: ");
    scanf("%d", &n);

    printf("Enter number of students: ");
    scanf("%d", &students);

    if(students > n)
    {
        printf("Number of students cannot be greater than books.\n");
        return 0;
    }

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        pages[i] = 100 + rand() % 901;
    }

    // Clock 1
    start = clock();

    int result = minimumPages(pages, n, students);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Minimum possible maximum pages = %d\n", result);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}