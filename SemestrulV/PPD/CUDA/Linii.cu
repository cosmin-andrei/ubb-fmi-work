#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <cstdlib>

// verificari eroare CUDA
#define cudaCheckError(ans) { gpuAssert((ans), __FILE__, __LINE__); }

inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true) {
    if (code != cudaSuccess) {
        std::cerr << "CUDA Error: " << cudaGetErrorString(code)
                  << " at " << file << ":" << line << std::endl;
        if (abort) exit(code);
    }
}


//kernel - proceseaza partitie (set de randuri din matrice)
//partitie - start/end
//startIndices/endIndices: vectori de indici pt def partitii (no. partitions = gridDim.x)
__global__ void convolutionKernel(int *mat, int M, int N, int n, const int *convMat,
                                  const int *startIndices, const int *endIndices) {
    // Fiecare bloc procesează o anumită partiţie
    int part = blockIdx.x;
    int start = startIndices[part];
    int end = endIndices[part];

    //alocare dinamica in shared memory
    extern __shared__ int sharedMem[];
    int *upArr = sharedMem; // randul de deasupra partiei start==0
    int *downArr = upArr + M; // randul de sub partitie end==N
    int *anteAux = downArr + M; // copie rand din anterior i1==0
    int *currentAux = anteAux + M; // rezultat convolutie rand curent
    int *oldRow = currentAux + M; // copie rand original

    // copiem sectiunile critice din matricea originala
    for (int j = threadIdx.x; j < M; j += blockDim.x) {
        upArr[j] = (start > 0) ? mat[(start - 1) * M + j] : mat[j]; //start>0 => rand precedent, altfel repetam rand 1
        downArr[j] = (end < N) ? mat[(end) * M + j] : mat[(N - 1) * M + j]; //end<N => rand index end, altfel last row
        anteAux[j] = mat[start * M + j]; //copie rand start
    }
    __syncthreads(); // sincronizare. toate threadurile trebuie sa ajunga aici

    // parcurgem partitia
    for (int i = start; i < end; i++) {
        // i>start => copiem randul i in oldRow
        if (i > start) {
            for (int j = threadIdx.x; j < M; j += blockDim.x)
                oldRow[j] = mat[i * M + j];
        }
        __syncthreads();

        // calcul convolutie
        for (int j = threadIdx.x; j < M; j += blockDim.x) {
            int sum = 0;

            // parcurgem kernelul de convolutie
            for (int i1 = 0; i1 < n; i1++) {
                for (int j1 = 0; j1 < n; j1++) {
                    int indexI = i + i1 - n / 2;
                    int indexJ = j + j1 - n / 2;
                    // verificam daca indexul este in afara matricei
                    if (indexI < 0) indexI = 0;
                    if (indexJ < 0) indexJ = 0;
                    if (indexI >= N) indexI = N - 1;
                    if (indexJ >= M) indexJ = M - 1;

                    int convVal = convMat[i1 * n + j1];

                    // daca suntem pe margine, folosim valorile din upArr, downArr, anteAux
                    if (i1 == 0 && i == start)
                        sum += upArr[indexJ] * convVal;
                    else if (i1 == n - 1 && i == end - 1)
                        sum += downArr[indexJ] * convVal;
                    else
                        sum += ((i1 == 0) ? anteAux[indexJ] : mat[indexI * M + indexJ]) * convVal;
                }
            }
            currentAux[j] = sum;
        }
        __syncthreads();

        // copiem randul anterior in anteAux
        for (int j = threadIdx.x; j < M; j += blockDim.x) {
            int origVal = (i == start) ? anteAux[j] : oldRow[j];
            anteAux[j] = origVal;
        }
        __syncthreads();

        // copiem rezultatul in matrice
        for (int j = threadIdx.x; j < M; j += blockDim.x)
            mat[i * M + j] = currentAux[j];
        __syncthreads();
    }
}

//lanseaza kernelul CUDA
//p-no. partitii, h_mat, h_convMat - matricile flat
void runConvolutionCUDA(int *h_mat, int N, int M, int n, int *h_convMat, int p) {
    size_t matSize = N * M * sizeof(int);
    size_t convSize = n * n * sizeof(int);

    int *d_mat = nullptr;
    int *d_convMat = nullptr;

    // Alocare memorie pe device
    cudaCheckError(cudaMalloc(&d_mat, matSize));
    cudaCheckError(cudaMalloc(&d_convMat, convSize));

    // Copiem datele din host în device
    cudaCheckError(cudaMemcpy(d_mat, h_mat, matSize, cudaMemcpyHostToDevice));
    cudaCheckError(cudaMemcpy(d_convMat, h_convMat, convSize, cudaMemcpyHostToDevice));

    // calculam indicii de start si end pentru fiecare partitie
    std::vector<int> h_start(p), h_end(p);
    int startRow = 0;
    int rowsPerPart = N / p;
    int remainingRows = N % p;

    // impartim liniile in p parti
    for (int k = 0; k < p; ++k) {
        int endRow = startRow + rowsPerPart;
        if (remainingRows > 0) {
            endRow++;
            remainingRows--;
        }
        h_start[k] = startRow;
        h_end[k] = endRow;
        startRow = endRow;
    }

    // alocare memorie pentru indicii de start si end
    size_t partsSize = p * sizeof(int);
    int *d_startIndices = nullptr, *d_endIndices = nullptr;

    // alocare memorie pe device
    cudaCheckError(cudaMalloc(&d_startIndices, partsSize));
    cudaCheckError(cudaMalloc(&d_endIndices, partsSize));
    cudaCheckError(cudaMemcpy(d_startIndices, h_start.data(), partsSize, cudaMemcpyHostToDevice));
    cudaCheckError(cudaMemcpy(d_endIndices, h_end.data(), partsSize, cudaMemcpyHostToDevice));

    int threadsPerBlock = 100; // threaduri per bloc
    size_t sharedMemSize = 5 * M * sizeof(int);  // dimensiunea memoriei partajate
    // lansam kernelul CUDA
    // p blocuri, threadsPerBlock threaduri, sharedMemSize memorie partajata
    //sharedMemSize - pentru cei 5 vectori auxiliari, care sunt accesati de toate threadurile

    for (int part = 0; part < p; ++part) {
        convolutionKernel<<<1, threadsPerBlock, sharedMemSize>>>(d_mat, M, N, n, d_convMat, d_startIndices, d_endIndices);
        cudaCheckError(cudaDeviceSynchronize());
    }

//    convolutionKernel<<< p, threadsPerBlock, sharedMemSize >>>(d_mat, M, N, n, d_convMat, d_startIndices, d_endIndices);
    cudaCheckError(cudaPeekAtLastError());
    cudaCheckError(cudaDeviceSynchronize());

    // copiem rezultatul inapoi in host
    cudaCheckError(cudaMemcpy(h_mat, d_mat, matSize, cudaMemcpyDeviceToHost));

    cudaFree(d_mat);
    cudaFree(d_convMat);
    cudaFree(d_startIndices);
    cudaFree(d_endIndices);
}

int *flattenMatrix(int **mat2D, int N, int M) {
    int *flat = new int[N * M];
    for (int i = 0; i < N; ++i)
        std::copy(mat2D[i], mat2D[i] + M, flat + i * M);
    return flat;
}

void copyFlatToMatrix(int *flat, int **mat2D, int N, int M) {
    for (int i = 0; i < N; ++i)
        std::copy(flat + i * M, flat + i * M + M, mat2D[i]);
}
