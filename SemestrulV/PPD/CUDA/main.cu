#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>

#include "Linii.h"
#include "Sequential.h"

int N, M, n, p;
int** mat;
int** convMat;

bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "Could not open one or both files for comparison." << std::endl;
        return false;
    }

    std::istreambuf_iterator<char> iter1(f1);
    std::istreambuf_iterator<char> iter2(f2);
    std::istreambuf_iterator<char> end;

    return std::equal(iter1, end, iter2);
}

void writeOutput(int** newMat) {
    std::ofstream fw("output.txt");
    if (!fw.is_open()) {
        std::cerr << "Could not open the file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fw << newMat[i][j] << " ";
        }
        fw << "\n";
    }
    fw.close();
}
void writeOutputSequentialForCorrectness(int** newMat) {
    std::ofstream fw("outputSequential.txt");
    if (!fw.is_open()) {
        std::cerr << "Could not open the file for writing." << std::endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fw << newMat[i][j] << " ";
        }
        fw << "\n";
    }
    fw.close();
}

void readInput() {
    std::ifstream scanner("data.txt");
    if (!scanner.is_open()) {
        std::cerr << "Could not open the file for reading." << std::endl;
        return;
    }

    scanner >> N >> M;

    // Allocate memory for the matrix mat
    mat = new int*[N];
    for (int i = 0; i < N; ++i)
        mat[i] = new int[M];

    if (N == 10000 && M == 10000) {
        std::mt19937 gen(47); // Fixed seed for consistent random values
        std::uniform_int_distribution<> dist(0, 6);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                mat[i][j] = dist(gen);
            }
        }

        scanner >> n;
        convMat = new int*[n];
        for (int i = 0; i < n; ++i)
            convMat[i] = new int[n];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanner >> convMat[i][j];
    } else {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                scanner >> mat[i][j];

        scanner >> n;
        convMat = new int*[n];
        for (int i = 0; i < n; ++i)
            convMat[i] = new int[n];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanner >> convMat[i][j];
    }

    scanner.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide the value of p as a command-line argument." << std::endl;
        return 1;
    }

    p = std::stoi(argv[1]);

    //citim datele initial pentru a face calculele secvential
    readInput();
    Sequential sequential(N, M, n, p,  mat, convMat);
    sequential.run();
    writeOutputSequentialForCorrectness( mat);

    //citim matricea din nou pt a incepe cu datele initiale si a calcula paralel
    readInput();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Convertim matricea 2D în format flat
    int *flatMat = flattenMatrix(mat, N, M);
    int *h_convMat = flattenMatrix(convMat, n, n);

    // Lansăm kernel‑ul CUDA pentru convoluţie
    runConvolutionCUDA(flatMat, N, M, n, h_convMat, p);

    // Copiem rezultatul în matricea 2D
    copyFlatToMatrix(flatMat, mat, N, M);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

    writeOutput(mat);
    std::cout<<std::setprecision(10);
    std::cout << elapsedTime.count()* 1E3 ;
    std::cout << std::endl;


    //comapram fisierele sa fie rezultatul la fel cu cel secvential
    if(compareFiles("output.txt","outputSequential.txt")) {
        std::cout << "FILES ARE THE SAME\n";
    }else {
        std::cerr << "FILES ARE THE DIFFERENT\n" << std::endl;
    }

    // Free allocated memory
    for (int i = 0; i < N; ++i)
        delete[] mat[i];
    delete[] mat;

    for (int i = 0; i < n; ++i)
        delete[] convMat[i];
    delete[] convMat;

    return 0;
}
