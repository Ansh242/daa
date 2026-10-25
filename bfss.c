#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int* items;
    int front;
    int rear;
    int capacity;
};

void initQueue(struct Queue* q, int capacity) {
    q->capacity = capacity;
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(struct Queue* q) {
    return q->rear == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == q->capacity - 1) {
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return item;
}

void freeQueue(struct Queue* q) {
    free(q->items);
}

void bfs(int** graph, int numVertices, int startVertex) {
    struct Queue q;
    initQueue(&q, numVertices);

    bool* visited = (bool*)calloc(numVertices, sizeof(bool));

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    printf("BFS Traversal: ");

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");

    free(visited);
    freeQueue(&q);
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
        bfs(graph, n, startVertex);
    }

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}