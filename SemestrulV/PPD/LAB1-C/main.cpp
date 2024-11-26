#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAX_N = 10000;
const int MAX_M = 10000;
const int MAX_n = 5;

int N, M, n, p;
//int F[MAX_N][MAX_M], result[MAX_N][MAX_M], C[MAX_n][MAX_n];
vector<vector<int>> F, C, result;

ofstream fout("output.txt");

void readInput_dinamic() {
    ifstream fin("date.txt");

    if (!fin) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    fin >> N >> M;
    F.resize(N, vector<int>(M));
    result.resize(N, vector<int>(M));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            fin >> F[i][j];

    fin >> n;
    C.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> C[i][j];
    fin.close();

}

void readInput() {

    ifstream fin("date.txt");
    if (!fin) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    fin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> F[i][j];
        }
    }

    fin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> C[i][j];
        }
    }
    fin.close();

}

void sequential() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (i + k < N && j + l < M) {
                        result[i][j] += F[i + k][j + l] * C[k][l];
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << result[i][j] << " ";
        }
        fout << endl;
    }
}

void calcLinii(int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < M; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (i + k < N && j + l < M) {
                        result[i][j] += F[i + k][j + l] * C[k][l];
                    }
                }
            }
        }
    }
}

void calcCol(int start, int end) {
    for (int i = 0; i < N; i++) {
        for (int j = start; j < end; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (i + k < N && j + l < M) {
                        result[i][j] += F[i + k][j + l] * C[k][l];
                    }
                }
            }
        }
    }
}

void conv_linii() {

    int start = 0, end = 0, i = 0;
    int cat = N / p, rest = N % p;
    vector<thread> tab_thr(p);

    while (start < N) {
        if (rest > 0) {
            end = start + cat + 1;
            rest--;
        } else {
            end = start + cat;
        }

        tab_thr[i++] = thread(calcLinii, start, end);
        start = end;
    }

    for (int j = 0; j < i; j++)
        tab_thr[j].join();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << result[i][j] << " ";
        }
        fout << endl;
    }

}

void conv_col() {
    int start = 0, end = 0, i = 0;
    int cat = M / p, rest = M % p;
    vector<thread> tab_thr(p);

    while (start < M) {
        if (rest > 0) {
            end = start + cat + 1;
            rest--;
        } else {
            end = start + cat;
        }

        tab_thr[i++] = thread(calcCol, start, end);
        start = end;
    }

    for (int j = 0; j < i; j++)
        tab_thr[j].join();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fout << result[i][j] << " ";
        }
        fout << endl;
    }

}


int main(int argc, char *argv[]) {

//    readInput();

    p = atoi(argv[1]);
    readInput_dinamic();

    auto start = chrono::high_resolution_clock::now();

//    sequential();
    conv_linii();
//     conv_col();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Elapsed time: " << setprecision(10) << elapsed.count();

    fout.close();
    return 0;
}
