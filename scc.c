#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack {
    int* items;
    int top;
    int capacity;
};

void initStack(struct Stack* s, int capacity) {
    s->capacity = capacity;
    s->items = (int*)malloc(capacity * sizeof(int));
    s->top = -1;
}

void push(struct Stack* s, int value) {
    s->top++;
    s->items[s->top] = value;
}

int pop(struct Stack* s) {
    int item = s->items[s->top];
    s->top--;
    return item;
}

bool isStackEmpty(struct Stack* s) {
    return s->top == -1;
}

void freeStack(struct Stack* s) {
    free(s->items);
}

void fillOrder(int** graph, int numVertices, int v, bool* visited, struct Stack* s) {
    visited[v] = true;

    for (int i = 0; i < numVertices; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            fillOrder(graph, numVertices, i, visited, s);
        }
    }

    push(s, v);
}

void dfsOnTranspose(int** transpose, int numVertices, int v, bool* visited) {
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < numVertices; i++) {
        if (transpose[v][i] == 1 && !visited[i]) {
            dfsOnTranspose(transpose, numVertices, i, visited);
        }
    }
}

void findSCCs(int** graph, int numVertices) {
    struct Stack s;
    initStack(&s, numVertices);

    bool* visited = (bool*)calloc(numVertices, sizeof(bool));

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            fillOrder(graph, numVertices, i, visited, &s);
        }
    }

    int** transpose = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        transpose[i] = (int*)malloc(numVertices * sizeof(int));
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            transpose[i][j] = graph[j][i];
        }
    }

    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    printf("\nStrongly Connected Components (SCCs):\n");
    int sccCount = 0;

    while (!isStackEmpty(&s)) {
        int v = pop(&s);

        if (!visited[v]) {
            sccCount++;
            printf("Component %d: ", sccCount);
            dfsOnTranspose(transpose, numVertices, v, visited);
            printf("\n");
        }
    }

    for (int i = 0; i < numVertices; i++) {
        free(transpose[i]);
    }
    free(transpose);
    free(visited);
    freeStack(&s);
}

int main() {
    int n;

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
            }
        }
    }

    printf("\nGenerated %dx%d Directed Graph Adjacency Matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    findSCCs(graph, n);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}