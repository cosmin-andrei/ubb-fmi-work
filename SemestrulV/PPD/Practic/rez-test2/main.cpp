// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "mpi.h"
#include "generate_numbers22.cpp"
#include <chrono>

using namespace std;

int sumDigit(int nr) {
    int sum = 0;
    while (nr) {
        sum += nr % 10;
        nr /= 10;
    }
    return sum;
}

void readFromFile(string filename, int &N, int *&nr, int &X) {
    ifstream fin(filename);

    if (!fin) {
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    fin >> X;
    fin >> N;
    nr = new int[N];

    for (int i = 0; i < N; i++) {
        fin >> nr[i];
    }

    fin.close();
}

void writeToFile(string filename, int *result, int length, int varA, int varB) {
    ofstream fout(filename);

    fout << varA << " " << varB << endl;
    fout << length << '\n';
    for (int i = 0; i < length; i++) {
        fout << result[i] << " ";
    }

    fout.close();
}

int main(int argc, char **argv) {

//    generateNumbers22(10);

    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    const string filename1 = "numbers.txt";
    const string outputFile = "result.txt";

    int N, chunk_size, X;
    int *nr;

    std::chrono::high_resolution_clock::time_point startTime;

    if (rank == 0) {

        startTime = chrono::high_resolution_clock::now();
        readFromFile(filename1, N, nr, X);

        MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int rest = N % (size - 1), start = 0;

        for (int i = 1; i < size; i++) {

            chunk_size = N / size;
            if (rest) {
                chunk_size++;
                rest--;
            }

            MPI_Send(&chunk_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            int *aux = new int[chunk_size];
            memcpy(aux, nr + start, chunk_size * sizeof(int));

            MPI_Send(aux, chunk_size, MPI_INT, i, 1, MPI_COMM_WORLD);

            start += chunk_size;
            delete[] aux;
        }

        //pt preluare date

        int varA = 0, varB = 0;
        int *result = new int[N];

        for (int i = 1; i < size; i++) {
            if (i == 1) {
                MPI_Recv(&varA, 1, MPI_INT, 1, 3, MPI_COMM_WORLD, &status);
                MPI_Recv(&varB, 1, MPI_INT, 1, 4, MPI_COMM_WORLD, &status);
            }

            MPI_Recv(result + (i - 1) * chunk_size, chunk_size, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
        }

        writeToFile("result.txt", result, N, varA, varB);


    } else {
        MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int chunk_size2;
        MPI_Recv(&chunk_size2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int *v1_adjusted = new int[chunk_size2];
        MPI_Recv(v1_adjusted, chunk_size2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        int varA = 0, varB = 0;
        if (rank != size - 1) {
            MPI_Recv(&varA, 1, MPI_INT, rank + 1, 3, MPI_COMM_WORLD, &status);
            MPI_Recv(&varB, 1, MPI_INT, rank + 1, 4, MPI_COMM_WORLD, &status);
        }

        int *result = new int[chunk_size2];

        for (int i = 0; i < chunk_size2; i++) {
            if (sumDigit(v1_adjusted[i]) < X) {
                result[i] = v1_adjusted[i] * 2;
                varA++;
            } else {
                result[i] = v1_adjusted[i] / 2;
                varB++;
            }
        }

        MPI_Send(&varA, 1, MPI_INT, rank - 1, 3, MPI_COMM_WORLD);
        MPI_Send(&varB, 1, MPI_INT, rank - 1, 4, MPI_COMM_WORLD);

        MPI_Send(result, chunk_size2, MPI_INT, 0, 2, MPI_COMM_WORLD);

        delete[] v1_adjusted;
        delete[] result;
    }

    MPI_Finalize();
    return 0;
}