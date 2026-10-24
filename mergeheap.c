#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define K 5

typedef struct
{
    int value;
    int arrayIndex;
    int elementIndex;
} Node;

Node heap[K];
int heapSize = 0;

void swap(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node x)
{
    int i = heapSize++;
    heap[i] = x;

    while(i > 0)
    {
        int p = (i - 1) / 2;

        if(heap[p].value <= heap[i].value)
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Node pop()
{
    Node result = heap[0];
    heap[0] = heap[--heapSize];

    int i = 0;

    while(1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if(left < heapSize &&
           heap[left].value < heap[smallest].value)
            smallest = left;

        if(right < heapSize &&
           heap[right].value < heap[smallest].value)
            smallest = right;

        if(smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

void mergeK(int a[][MAX], int sizes[], int k,
            int result[], int total)
{
    int i, pos = 0;
    heapSize = 0;

    for(i = 0; i < k; i++)
    {
        if(sizes[i] > 0)
        {
            Node x;
            x.value = a[i][0];
            x.arrayIndex = i;
            x.elementIndex = 0;
            push(x);
        }
    }

    while(heapSize > 0)
    {
        Node current = pop();
        int row = current.arrayIndex;
        int next = current.elementIndex + 1;

        result[pos++] = current.value;

        if(next < sizes[row])
        {
            Node x;
            x.value = a[row][next];
            x.arrayIndex = row;
            x.elementIndex = next;
            push(x);
        }
    }
}

int main()
{
    static int a[K][MAX];
    static int result[MAX];

    int sizes[K];
    int n, i, j;
    int base, remainder;

    clock_t start, end;
    double time_taken;

    printf("Enter total number of elements (5 to %d): ", MAX);
    scanf("%d", &n);

    if(n < K || n > MAX)
    {
        printf("Invalid n.\n");
        return 0;
    }

    base = n / K;
    remainder = n % K;

    // Generate K sorted arrays.
    // Input generation is outside the timed section.
    int nextValue = 0;

    for(i = 0; i < K; i++)
    {
        sizes[i] = base + (i < remainder ? 1 : 0);

        for(j = 0; j < sizes[i]; j++)
        {
            a[i][j] = nextValue;
            nextValue += 1 + rand() % 3;
        }
    }

    // Clock 1
    start = clock();

    mergeK(a, sizes, K, result, n);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Merged array (first 10 elements or fewer):\n");

    for(i = 0; i < n && i < 10; i++)
        printf("%d ", result[i]);

    printf("\nExecution Time = %f seconds\n", time_taken);

    return 0;
}