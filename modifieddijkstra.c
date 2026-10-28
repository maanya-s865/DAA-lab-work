
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int main() {
    int graph[MAX][MAX];
    int capacity[MAX];
    int visited[MAX] = {0};
    int n, source, i, j;
    int best, u, candidate;
    clock_t start, end;
    double time_taken;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter capacity matrix (0 means no edge):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] < 0) {
                printf("Capacities cannot be negative.\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    if (source < 0 || source >= n) {
        printf("Invalid source vertex!\n");
        return 1;
    }

    start = clock();

    for (i = 0; i < n; i++)
        capacity[i] = -1;

    /* The source has unlimited initial bottleneck capacity. */
    capacity[source] = INT_MAX;

    for (i = 0; i < n; i++) {
        best = -1;
        u = -1;

        /* Select the unvisited vertex with maximum capacity. */
        for (j = 0; j < n; j++) {
            if (!visited[j] && capacity[j] > best) {
                best = capacity[j];
                u = j;
            }
        }

        if (u == -1 || best == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] > 0) {
                candidate = capacity[u] < graph[u][j]
                            ? capacity[u] : graph[u][j];

                if (candidate > capacity[j])
                    capacity[j] = candidate;
            }
        }
    }

    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nMaximum bottleneck capacities from vertex %d:\n",
           source);

    for (i = 0; i < n; i++) {
        if (i == source)
            printf("Vertex %d: Source\n", i);
        else if (capacity[i] == -1)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, capacity[i]);
    }

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
