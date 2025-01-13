#include <chrono>
#include <functional>
#include <iostream>
#include <omp.h>

#define M 100
#define P 100

void array_sum_seq(int *a, int *b, int *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void array_sum_par(int *a, int *b, int *c, int n, int no_threads) {
    omp_set_num_threads(no_threads);
    int i;
#pragma omp parallel for private(i) shared(a, b, c) schedule(guided)
    for (i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void array_prod_seq(int *a, int *b, int *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i];
    }
}

void array_prod_par(int *a, int *b, int *c, int n, int no_threads) {
    omp_set_num_threads(no_threads);
    int i;
#pragma omp parallel for private(i) shared(a, b, c) schedule(guided)
    for (i = 0; i < n; i++) {
        c[i] = a[i] * b[i];
    }
}

void timer_func(std::function<void()> func) {
    auto start = std::chrono::system_clock::now();
    func();
    auto end = std::chrono::system_clock::now();
    auto dif = end - start;

    std::cout << "Time: " << dif.count() / 1e6 << " ms" << std::endl;
}

void validate_sum(int *a, int *b, int *c, int n) {
    for (int i = 0; i < n; i++) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Error at index " << i << std::endl;
            break;
        }
    }
}

void validate_prod(int *a, int *b, int *c, int n) {
    for (int i = 0; i < n; i++) {
        if (c[i] != a[i] * b[i]) {
            std::cout << "Error at index " << i << std::endl;
            break;
        }
    }
}

int scalar_product_seq(int *a, int *b, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int scalar_product_par(int *a, int *b, int n, int no_threads) {
    omp_set_num_threads(no_threads);
    int i, sum = 0, total_sum = 0;
#pragma omp parallel private(i) shared(a, b) firstprivate(sum)
    {
#pragma omp for schedule(static)
        for (i = 0; i < n; i++) {
            sum += a[i] * b[i];
        }
#pragma omp atomic
        total_sum += sum;
    }

    return total_sum;
}

int scalar_product_par_reduce(int *a, int *b, int n, int no_threads) {
    omp_set_num_threads(no_threads);
    int i, sum = 0;
#pragma omp parallel for private(i) shared(a, b) schedule(static) reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }

    return sum;
}

void sumMatSeq(int m1[M][P], int m2[M][P], int m3[M][P]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            m3[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void sumMatPar(int m1[M][P], int m2[M][P], int m3[M][P], int no_threads) {
    int i, j;
    omp_set_num_threads(no_threads);
#pragma omp parallel for private(i, j) shared(m1, m2, m3) schedule(dynamic, 1000)
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            m3[i][j] += m1[i][j] + m2[j][j];

        }
    }
}

void sumMatPar2(int m1[M][P], int m2[M][P], int m3[M][P], int no_threads) {
    int i, j;
    omp_set_num_threads(no_threads);
#pragma omp parallel for private(i, j) shared(m1, m2, m3) schedule(static) collapse(2)
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            m3[i][j] += m1[i][j] + m2[j][j];

        }
    }
}

void allSeq(int* a, int* b, int* c1, int* c2, int n) {
    array_sum_seq(a, b, c1, n);
    array_prod_seq(a, b, c2, n);
    scalar_product_seq(a, b, n);
}

void allPar(int* a, int* b, int* c1, int* c2, int n, int no_threads) {
    omp_set_num_threads(no_threads);
#pragma omp parallel sections
    {
#pragma omp section
        array_sum_par(a, b, c1, n, no_threads);
#pragma omp section
        array_prod_par(a, b, c2, n, no_threads);
#pragma omp section
        scalar_product_par(a, b, n, no_threads);
    };
}

int main() {
    int n = 100000000;
    int limit = 1000;

    int *a = new int[n];
    int *b = new int[n];
    int *c = new int[n];

    for (int i = 0; i < n; i++) {
        a[i] = i % limit;
        b[i] = i % limit;
    }

    timer_func([&]() {
        array_sum_seq(a, b, c, n);
    });
    validate_sum(a, b, c, n);

    int no_threads = 6;
    timer_func([&]() {
        array_sum_par(a, b, c, n, no_threads);
    });
    validate_sum(a, b, c, n);

    timer_func([&]() {
        array_prod_seq(a, b, c, n);
    });
    validate_prod(a, b, c, n);

    timer_func([&]() {
        array_prod_par(a, b, c, n, no_threads);
    });
    validate_prod(a, b, c, n);

    int seq_sum;
    timer_func([&]() {
        seq_sum = scalar_product_seq(a, b, n);
    });

    int par_sum;
    timer_func([&]() {
        par_sum = scalar_product_par(a, b, n, no_threads);
    });

    int par_sum_reduce;
    timer_func([&]() {
        par_sum_reduce = scalar_product_par_reduce(a, b, n, no_threads);
    });


    int m1[M][P], m2[M][P], m3[M][P];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            m1[i][j] = i + j;
            m2[i][j] = i + j;
        }
    }

    timer_func([&]() {
        sumMatSeq(m1, m2, m3);
    });

    timer_func([&]() {
        sumMatPar(m1, m2, m3, no_threads);
    });

    timer_func([&]() {
        sumMatPar2(m1, m2, m3, no_threads);
    });

    int* c1 = new int[n];
    int* c2 = new int[n];

    timer_func([&]() {
        allSeq(a, b, c1, c2, n);
    });

    timer_func([&]() {
        allPar(a, b, c1, c2, n, no_threads);
    });

    return 0;
}