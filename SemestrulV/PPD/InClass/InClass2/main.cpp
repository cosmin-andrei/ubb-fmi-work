//
// Created by Cosmin on 10/14/2024.
//

#include <iostream>
#include <thread>
#include <functional>
#include <vector>
//#include <valarray>
#include <cmath>


#define length 10000000

using namespace std;

//double a[length], b[length], c[length];


void init_vector(double a[]) {
    for (int i = 0; i < length; i++)
        a[i] = i;
}

void calculeazaSuma(double a[], double b[], double c[], int start, int end, function<double(double, double)> fct) {
    for (int i = start; i < end; i++)
       c[i] = fct(a[i], b[i]);
}

void
parallel_calculeazaSuma(double a[], double b[], double c[], const int n_threads, function<double(double, double)> fct) {
    int start = 0, end = 0, i = 0;
    int cat = length / n_threads, rest = length % n_threads;
//    thread tab_thr[n_threads];
    vector<thread> tab_thr(n_threads);

    while (start < length) {
        if (rest > 0) {
            end = start + cat + 1;
            rest--;
        } else {
            end = start + cat;
        }

        tab_thr[i++] = thread(calculeazaSuma, a, b, c, start, end, fct);
        start = end;
    }

    for (i = 0; i < n_threads; i++)
        tab_thr[i].join();

}

void cycle_sum(double a[], double b[], double c[], int start, int jump, function<double(double, double)> fct) {
    for (int i = start; i < length; i += jump)
        c[i] = fct(a[i], b[i]);
}

void
cicle_calculeazaSuma(double a[], double b[], double c[], const int n_threads, function<double(double, double)> fct) {
    thread tab_thr[n_threads];
    for (int i = 0; i < n_threads; i++)
        tab_thr[i] = thread(cycle_sum, a, b, c, i, n_threads, fct);

    for (int i = 0; i < n_threads; i++)
        tab_thr[i].join();
}

bool is_ok(double a[], double b[]) {
    for (int i = 0; i < length; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

int main() {

//    double a[length], b[length], c[length];

    double *a = new double[length];
    double *b = new double[length];
    double *c = new double[length];
    double *e = new double[length];
    double *f = new double[length];
    init_vector(a);
    auto t_start = chrono::steady_clock::now();
    calculeazaSuma(a, b, f, 0, length, [=](double a, double b) { return sqrt(pow(a,3)+ pow(b,3)); });
    auto t_final1 = chrono::steady_clock::now();
    cout << "Time sequencial: " << chrono::duration<double, milli>(t_final1 - t_start).count() << " ms" << endl;
    parallel_calculeazaSuma(a, b, c, 4, [=](double a, double b) { return sqrt(pow(a,3)+ pow(b,3));});
    auto t_final2 = chrono::steady_clock::now();
    auto diff = t_final2 - t_final1;
    cout << "Time parallel: " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
    cicle_calculeazaSuma(a, b, e, 4, [=](double a, double b) { return sqrt(pow(a,3)+ pow(b,3)); });
    auto t_final3 = chrono::steady_clock::now();
    diff = t_final3 - t_final2;
    cout << "Time parallel: " << chrono::duration<double, milli>(diff).count() << " ms" << endl;

    cout<<"Is ok: "<<is_ok(c, e)<<endl;
    cout<<"Is ok: "<<is_ok(c, f)<<endl;
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] e;
    delete[] f;

    return 0;
}
