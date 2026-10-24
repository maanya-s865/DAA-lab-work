#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 50000

typedef struct
{
    char ch;
    int count;
} Node;

Node heap[256];
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

        if(heap[p].count >= heap[i].count)
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
        int largest = i;

        if(left < heapSize &&
           heap[left].count > heap[largest].count)
            largest = left;

        if(right < heapSize &&
           heap[right].count > heap[largest].count)
            largest = right;

        if(largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return result;
}

int rearrange(char s[], char result[])
{
    int freq[256] = {0};
    int i, n = strlen(s);

    heapSize = 0;

    for(i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for(i = 0; i < 256; i++)
    {
        if(freq[i] > 0)
        {
            Node x;
            x.ch = (char)i;
            x.count = freq[i];
            push(x);
        }
    }

    Node previous;
    previous.ch = '\0';
    previous.count = 0;

    int pos = 0;

    while(heapSize > 0)
    {
        Node current = pop();

        result[pos++] = current.ch;
        current.count--;

        if(previous.count > 0)
            push(previous);

        previous = current;
    }

    result[pos] = '\0';

    return pos == n;
}

int main()
{
    char s[MAX + 1];
    char result[MAX + 1];

    clock_t start, end;
    double time_taken;

    printf("Enter a string (maximum %d characters): ", MAX);
    scanf("%50000s", s);

    // Clock 1
    start = clock();

    int possible = rearrange(s, result);

    // Clock 2
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    if(possible)
        printf("Rearranged string = %s\n", result);
    else
        printf("No valid rearrangement exists.\n");

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}