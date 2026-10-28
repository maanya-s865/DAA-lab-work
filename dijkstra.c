
#include <stdio.h>
#include <time.h>

#define MAX 100
#define INF 1000000000

int main() {
    int graph[MAX][MAX];
    int dist[MAX], visited[MAX] = {0};
    int n, source, i, j;
    int min, u;
    clock_t start, end;
    double time_taken;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter adjacency matrix (0 means no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
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
        dist[i] = INF;

    dist[source] = 0;

    for (i = 0; i < n; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] > 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][j] < dist[j]) {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nShortest distances from vertex %d:\n", source);
    for (i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("Vertex %d: Unreachable\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
