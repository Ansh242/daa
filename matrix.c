#include <stdio.h>

#define N 4 // Size of the matrices (must be a power of 2 for this basic version)

// Function to add two matrices
void add(int n, int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function for Divide and Conquer Matrix Multiplication
void divideAndConquerMultiply(int n, int A[N][N], int B[N][N], int C[N][N]) {
    // Base case: if matrix size is 1x1
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    
    // Temporary sub-matrices
    int A11[N][N], A12[N][N], A21[N][N], A22[N][N];
    int B11[N][N], B12[N][N], B21[N][N], B22[N][N];
    int C11[N][N], C12[N][N], C21[N][N], C22[N][N];
    int temp1[N][N], temp2[N][N];

    // Initialize sub-matrices to 0
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];

            C11[i][j] = 0; C12[i][j] = 0; C21[i][j] = 0; C22[i][j] = 0;
        }
    }

    // Step 1: Compute C11 = (A11 * B11) + (A12 * B21)
    divideAndConquerMultiply(newSize, A11, B11, temp1);
    divideAndConquerMultiply(newSize, A12, B21, temp2);
    add(newSize, temp1, temp2, C11);

    // Step 2: Compute C12 = (A11 * B12) + (A12 * B22)
    divideAndConquerMultiply(newSize, A11, B12, temp1);
    divideAndConquerMultiply(newSize, A12, B22, temp2);
    add(newSize, temp1, temp2, C12);

    // Step 3: Compute C21 = (A21 * B11) + (A22 * B21)
    divideAndConquerMultiply(newSize, A21, B11, temp1);
    divideAndConquerMultiply(newSize, A22, B21, temp2);
    add(newSize, temp1, temp2, C21);

    // Step 4: Compute C22 = (A21 * B12) + (A22 * B22)
    divideAndConquerMultiply(newSize, A21, B12, temp1);
    divideAndConquerMultiply(newSize, A22, B22, temp2);
    add(newSize, temp1, temp2, C22);

    // Combine sub-matrices back into result matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

int main() {
    int A[N][N] = {
        {1, 2, 1, 2},
        {3, 4, 3, 4},
        {1, 1, 1, 1},
        {2, 2, 2, 2}
    };

    int B[N][N] = {
        {2, 0, 1, 2},
        {0, 2, 3, 4},
        {1, 1, 1, 1},
        {2, 2, 0, 0}
    };

    int C[N][N] = {0};

    divideAndConquerMultiply(N, A, B, C);

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}