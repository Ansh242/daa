#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs(int** graph, int numVertices, int currentVertex, bool* visited) {
    visited[currentVertex] = true;
    printf("%d ", currentVertex);

    for (int i = 0; i < numVertices; i++) {
        if (graph[currentVertex][i] == 1 && !visited[i]) {
            dfs(graph, numVertices, i, visited);
        }
    }
}

int main() {
    int n, startVertex;

    printf("Enter number of vertices (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int** graph = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j];
            }
        }
    }

    printf("\nGenerated %dx%d Adjacency Matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &startVertex);

    if (startVertex >= 0 && startVertex < n) {
        bool* visited = (bool*)calloc(n, sizeof(bool));
        
        printf("DFS Traversal: ");
        dfs(graph, n, startVertex, visited);
        printf("\n");

        free(visited);
    }

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}