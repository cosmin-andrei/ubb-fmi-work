#include <iostream>
#include <fstream>
#include "mpi.h"
#include "generate_numbers.cpp"

using namespace std;

int *v;

int sumDigits(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
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

int f(int nr, int X, int &flag) {
    if (sumDigits(nr) < X) {
        flag = 1;
        return nr * 2;
    } else {
        flag = 2;
        return nr / 2;
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // nr de procese

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rankul procesului

    MPI_Status status;
    const string filename1 = "numbers.txt";
    const string outputFile = "result.txt";

    int *result;
    int X, N;
    std::chrono::high_resolution_clock::time_point startTime;

    if (rank == 0) {
        int chunk_size = 0;
        int *nr;
        readFromFile(filename1, N, nr, X);
        startTime = chrono::high_resolution_clock::now();

        MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int rest = N % (size - 1);
        int start = 0;
        chunk_size = N / size; // dimensiunea de bază

        for (int i = 1; i < size; i++) {
            int current_chunk_size = chunk_size;
            if (rest) {
                current_chunk_size++;
                rest--;
            }

            MPI_Send(&current_chunk_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            int* aux = new int[current_chunk_size];
            memcpy(aux, nr + start, current_chunk_size * sizeof(int));
            MPI_Send(aux, current_chunk_size, MPI_INT, i, 1, MPI_COMM_WORLD);
            start += current_chunk_size;
            delete[] aux;
        }

        result = new int[N];
        int varA = 0, varB = 0;
        for (int i = 1; i < size; i++) {
            MPI_Recv(result + (i - 1) * chunk_size, chunk_size, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            if (i == 1) {
                MPI_Recv(&varA, 1, MPI_INT, 1, 3, MPI_COMM_WORLD, &status);
                MPI_Recv(&varB, 1, MPI_INT, 1, 4, MPI_COMM_WORLD, &status);
            }
        }

        cout << "VarA: " << varA << " " << "VarB: " << varB << endl;
        for (int i = 0; i < N; i++) {
            cout << result[i] << " ";
        }
        cout << endl;

        auto endTime = chrono::high_resolution_clock::now();
        double difference = chrono::duration<double, milli>(endTime - startTime).count();
        cout << difference << endl;

        delete[] nr;
        delete[] result;

    } else {
        MPI_Bcast(&X, 1, MPI_INT, 0, MPI_COMM_WORLD);

        int chunk_size;
        MPI_Recv(&chunk_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int* v1_adjusted = new int[chunk_size];
        MPI_Recv(v1_adjusted, chunk_size, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        int varA = 0, varB = 0;

        if (rank != size - 1) {
            MPI_Recv(&varA, 1, MPI_INT, rank + 1, 3, MPI_COMM_WORLD, &status);
            MPI_Recv(&varB, 1, MPI_INT, rank + 1, 4, MPI_COMM_WORLD, &status);
        }

        for (int i = chunk_size; i >= 0; i--) {
            int flag = 0;
            v1_adjusted[i] = f(v1_adjusted[i], X, flag);
            if (flag == 1) {
                varA++;
            } else if (flag == 2) {
                varB++;
            }
        }

        MPI_Send(v1_adjusted, chunk_size, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&varA, 1, MPI_INT, rank - 1, 3, MPI_COMM_WORLD);
        MPI_Send(&varB, 1, MPI_INT, rank - 1, 4, MPI_COMM_WORLD);
        delete[] v1_adjusted;
    }

    MPI_Finalize();
    return 0;
}