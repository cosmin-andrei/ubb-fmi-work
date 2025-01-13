#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstring>

using namespace std;

int N, M, n, p;
int **F, **C;
int remainingThreads;
std::mutex barrierMutex;
std::condition_variable barrierCV;

ofstream fout("output.txt");

void readInput_dinamic() {
    ifstream fin("date.txt");

    if (!fin) {
        cerr << "Error opening input file" << endl;
        exit(1);
    }

//    fin >> N >> M;
//    F = new int *[N];
//    for (int i = 0; i < N; ++i)
//        F[i] = new int[M];
//
//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < M; j++)
//            fin >> F[i][j];

    N = 10000;
    M = 10000;
    F = new int *[N];
    for (int i = 0; i < N; i++)
        F[i] = new int[M];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            F[i][j] = rand() % 100;


    fin >> n;
    C = new int *[n];
    for (int i = 0; i < n; ++i)
        C[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> C[i][j];

    fin.close();
}

//bariera pt sincronizare threaduri - cu mutex si var cond
void barrierWait() {
    std::unique_lock<std::mutex> lock(barrierMutex);
    remainingThreads--;
    if (remainingThreads == 0) {
        remainingThreads = p; //reset for next barrier
        barrierCV.notify_all();
    } else {
        barrierCV.wait(lock, []() { return remainingThreads == p; }); //asteapta conditia
        //conditia = toate threadurile isi actualizeaza frontierele
    }
}

void workerThread(int start, int end) {
    //up-down submatrice
    int *up = new int[M];
    int *down = new int[M];

    //ca la secvential
    int *prev = new int[M];
    int *curr = new int[M];

    //iau frontierele
    if (start > 0) //in interior matrice
        std::copy(F[start - 1], F[start - 1] + M, up);
    else //bordura
        std::copy(F[0], F[0] + M, up);

    if (end < N)
        std::copy(F[end], F[end] + M, down);
    else
        std::copy(F[N - 1], F[N - 1] + M, down);

    std::copy(F[start], F[start] + M, prev);

    barrierWait(); //sincronizare

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int i1 = 0; i1 < n; i1++) {
                for (int j1 = 0; j1 < n; j1++) {

                    //indexul din matricea F
                    int indexI = i + i1 - n / 2;
                    int indexJ = j + j1 - n / 2;

                    //bordura
                    if (indexI < 0) indexI = 0;
                    if (indexJ < 0) indexJ = 0;
                    if (indexI >= N) indexI = N - 1;
                    if (indexJ >= M) indexJ = M - 1;

                    //daca e pe prima linie
                    if (i1 == 0 && i == start)
                        sum += up[indexJ] * C[i1][j1];
                    //daca e pe ultima linie
                    else if (i1 == n - 1 && i == end - 1)
                        sum += down[indexJ] * C[i1][j1];
                    //in rest
                    else
                        sum += ((i1 == 0) ? prev[indexJ] : F[indexI][indexJ]) * C[i1][j1];
                }
            }
            //salvez in current
            curr[j] = sum;
        }

        //copiez in prev - pt a putea calcula urmatoarea linie
        std::copy(F[i], F[i] + M, prev);
        //copiez in matricea F - actualizez
        std::copy(curr, curr + M, F[i]);
    }

    delete[] up;
    delete[] down;
    delete[] prev;
    delete[] curr;
}

void sequentialProcess() {

    int *prev = new int[M];
    int *curr = new int[M];

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
                        sum += prev[indexJ] * C[i1][j1];
                    } else {
                        sum += F[indexI][indexJ] * C[i1][j1];
                    }
                }
            }
            curr[j] = sum;
        }

        // Copy current row to anteAux for next iteration
        std::memcpy(prev, C[i], M * sizeof(int));

        // Update mat with the results of the current convolution row
        std::memcpy(F[i], curr, M * sizeof(int));
    }
}

void run() {
    int startRow = 0, endRow;
    int rowsPerThread = N / p;
    int remainingRows = N % p;

    std::vector<std::thread> threads;

    for (int k = 0; k < p; ++k) {
        endRow = startRow + rowsPerThread;
        if (remainingRows > 0) {
            endRow++;
            remainingRows--;
        }

        threads.emplace_back(workerThread, startRow, endRow);
        startRow = endRow;
    }

    for (auto &th: threads)
        th.join();
}

// Functie de eliberare a memoriei
void freeMemory() {
    for (int i = 0; i < N; ++i) delete[] F[i];
    delete[] F;
    for (int i = 0; i < n; ++i) delete[] C[i];
    delete[] C;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || (p = atoi(argv[1])) <= 0) {
        cerr << "Usage: " << argv[0] << " <number_of_threads>" << endl;
        return 1;
    }

    remainingThreads = p;
    readInput_dinamic();

    if (!fout) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

//    auto start = chrono::high_resolution_clock::now();
//    run();
//    auto end = chrono::high_resolution_clock::now();
//    chrono::duration<double, std::milli> elapsed = end - start;
//    cout << "OK" << endl;
//    cout << elapsed.count();

    auto startSeq = chrono::high_resolution_clock::now();
    sequentialProcess();
    auto endSeq = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> elapsedSeq = endSeq - startSeq;
    cout << "OK" << endl;
    cout << elapsedSeq.count();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << F[i][j] << " ";
        }
        fout << endl;
    }

    fout.close();
    freeMemory();
    return 0;
}
