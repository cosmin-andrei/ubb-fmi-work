#ifndef LINII_H
#define LINII_H

#include <cuda_runtime.h>
#include <vector>

// Macro pentru verificarea erorilor CUDA
#define cudaCheckError(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true);

// Kernel CUDA care procesează o partiţie (set de rânduri) din matrice.
__global__ void convolutionKernel(int *mat, int M, int N, int n, const int *convMat,
                                  const int *startIndices, const int *endIndices);

// Funcţie host ce lansează kernel‑ul CUDA.
void runConvolutionCUDA(int *h_mat, int N, int M,
                        int n, int *h_convMat,
                        int p);

// Convertește o matrice 2D (int**) de dimensiune N x M într-un vector contiguu de int.
int* flattenMatrix(int **mat2D, int N, int M);

// Copiază datele dintr-un vector flat (de lungime N*M) în matricea 2D (int**).
void copyFlatToMatrix(int *flat, int **mat2D, int N, int M);

#endif // LINII_H
