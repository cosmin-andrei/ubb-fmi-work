#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

class Sequential {
private:
    int N, M, n, p;
    int** mat;
    int** convMat;

public:
    Sequential(int N, int M, int n, int p, int** mat, int** convMat);
    void run();
};

#endif // SEQUENTIAL_H
