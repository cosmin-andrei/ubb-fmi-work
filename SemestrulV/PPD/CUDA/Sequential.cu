#include "Sequential.h"
#include <cstring> // for std::memcpy


Sequential::Sequential(int N, int M, int n, int p, int** mat, int** convMat)
        : N(N), M(M), n(n), p(p), mat(mat), convMat(convMat) {}

void Sequential::run() {
    // Allocate auxiliary arrays dynamically
    int* anteAux = new int[M];
    int* currentAux = new int[M];

    // Initialize anteAux with the first row of mat
    std::memcpy(anteAux, mat[0], M * sizeof(int));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int i1 = 0; i1 < n; ++i1) {
                for (int j1 = 0; j1 < n; ++j1) {
                    int indexI = i + i1 - n / 2;
                    int indexJ = j + j1 - n / 2;

                    // Apply boundary conditions
                    if (indexI < 0) indexI = 0;
                    if (indexJ < 0) indexJ = 0;
                    if (indexI >= N) indexI = N - 1;
                    if (indexJ >= M) indexJ = M - 1;

                    // Perform convolution
                    if (i1 == 0) {
                        sum += anteAux[indexJ] * convMat[i1][j1];
                    } else {
                        sum += mat[indexI][indexJ] * convMat[i1][j1];
                    }
                }
            }
            currentAux[j] = sum;
        }

        // Copy current row to anteAux for next iteration
        std::memcpy(anteAux, mat[i], M * sizeof(int));

        // Update mat with the results of the current convolution row
        std::memcpy(mat[i], currentAux, M * sizeof(int));
    }

    // Free dynamically allocated memory
    delete[] anteAux;
    delete[] currentAux;
}
