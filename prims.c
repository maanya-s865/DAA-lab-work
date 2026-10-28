
#include <stdio.h>
#include <time.h>

#define MAX 100

int main() {
    int graph[MAX][MAX];
    int visited[MAX] = {0};
    int n, i, j, edges = 0;
    int min, u = -1, v = -1;
    int totalCost = 0;
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

    start = clock();

    visited[0] = 1;

    while (edges < n - 1) {
        min = 2147483647;
        u = -1;
        v = -1;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && graph[i][j] > 0 &&
                        graph[i][j] < min) {
                        min = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1) {
            printf("Graph is disconnected; MST does not exist.\n");
            return 0;
        }

        printf("Edge %d - %d : weight %d\n", u, v, min);
        totalCost += min;
        visited[v] = 1;
        edges++;
    }

    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Total MST weight = %d\n", totalCost);
    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
