#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

struct Subset {
    int parent;
    int rank;
};

int compareEdges(const void *a, const void *b) {
    const struct Edge *edgeA = (const struct Edge *)a;
    const struct Edge *edgeB = (const struct Edge *)b;
    if (edgeA->weight < edgeB->weight) return -1;
    if (edgeA->weight > edgeB->weight) return 1;
    return 0;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int kruskalMST(int V, int E, struct Edge edges[]) {
    qsort(edges, E, sizeof(struct Edge), compareEdges);
    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    int minCost = 0;
    int edgesCount = 0;
    for (int i = 0; i < E; i++) {
        int rootSrc = find(subsets, edges[i].src);
        int rootDest = find(subsets, edges[i].dest);
        if (rootSrc != rootDest) {
            minCost += edges[i].weight;
            unionSets(subsets, rootSrc, rootDest);
            edgesCount++;
            if (edgesCount == V - 1) break;
        }
    }
    free(subsets);
    return (edgesCount == V - 1 || V <= 1) ? minCost : -1;
}

int main() {
    int V = 4;
    int E = 5;
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    int minCost = kruskalMST(V, E, edges);
    printf("Minimum Cost Spanning Tree: %d\n", minCost);
    return 0;
}