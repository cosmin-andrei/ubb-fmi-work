#include <iostream>
#include "mpi.h"
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void saveToFile(const string &filePath, int *result, int length) {

    ofstream fout(filePath);
    fout << length << '\n';
    for (int i = 0; i < length; i++) {
        fout << result[i] << " ";
    }
    fout.close();
}

void generateNumbers(string filename, int digits) {
    ofstream out(filename);

    //utilizez timp curent pt randomizare
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    out << digits << '\n';
    //generez anterior si le pun in fisier
    for (int i = 0; i < digits; i++) {
        int digit;
        if (i == 0)
            digit = rand() % 9 + 1;
        else
            digit = rand() % 10;
        out << digit << " ";
    }
    out.close();
}

bool fileEq(const std::string &file1, const std::string &file2) {
    std::ifstream f1(file1), f2(file2);

    int size1, size2;
    std::vector<int> vec1, vec2;

    vec1.resize(size1);
    vec2.resize(size2);

    // Compare sizes
    if (size1 != size2) {
        return false;
    }

    // Compare elements
    for (int i = 0; i < size1; ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }

    return true;
}

void seq(const string &path, const string &pathSec) {
    ifstream f(path);

    int N1, N2; //lenght numbers
    int *nr1 = nullptr; //first number
    int *nr2 = nullptr; //second number
    int *sum = nullptr; //sum
    auto t_start = chrono::steady_clock::now();

    f >> N1;
    nr1 = new int[N1];
    for (int i = 0; i < N1; i++) {
        f >> nr1[i];
    }

    f.close();

    f.open(pathSec);
    f >> N2;
    nr2 = new int[N2];
    for (int i = 0; i < N2; i++) {
        f >> nr2[i];
    }

    //max length
    int len = max(N1, N2) + 1;
    sum = new int[len];
    for (int i = 0; i < len; i++)
        sum[i] = 0;

    //parcurgere numere
    int i = N1 - 1, j = N2 - 1, k = 0;
    int flag = 0, nr = 0; //carry, sum curr

    while (i >= 0 && j >= 0) {
        //sum digits
        nr = nr1[i] + nr2[j] + flag;
        if (nr > 9)
            //keep last digit, carry - 1
            nr = nr % 10, flag = 1;
        else
            flag = 0;
        //adaug in vect de suma
        sum[k++] = nr;
        i--;
        j--;
    }

    //adun cifrele ramase in oricare dintre numere
    if (i >= 0) {
        while (i >= 0) {
            nr = nr1[i] + flag;
            if (nr > 9)
                nr = nr % 10, flag = 1;
            else
                flag = 0;

            sum[k++] = nr;
            i--;
        }
    } else if (j >= 0) {
        while (j >= 0) {
            nr = nr2[j] + flag;
            if (nr > 9)
                nr = nr % 10, flag = 1;
            else
                flag = 0;

            sum[k++] = nr;
            j--;
        }
    }

    //daca exista carry, il adaug
    if (flag)
        sum[k++] = 1;
    //update length
    len = k;


    auto t_final = chrono::steady_clock::now();
    auto diff = t_final - t_start;
    cout << chrono::duration<double, milli>(diff).count();

    saveToFile("Numar3.txt", sum, len);
    delete[] nr1;
    delete[] nr2;
    delete[] sum;
}

void sendRecvVar(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, numProcs; //rank proc and no procs
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    int l1 = 0, l2 = 0, resL = 0, chunk = 0, carry = 0;
    int *nr_sum = nullptr; // vectorul de suma

    // chunkuri pt numere - primul si al doilea
    //aproximativ egale
    //folosite pt a trimite catre procese bucati de numere de dimensiune chunk
    int *chunk1 = nullptr;
    int *chunk2 = nullptr;

    if (rank == 0) {
        ifstream f(argv[1]);
        ifstream f2(argv[2]);

        if (!f || !f2) {
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        f >> l1;
        f2 >> l2;

        resL = max(l1, l2) + 1; // max length si carry
        chunk = (resL + numProcs - 1) / numProcs; // dim. chunk per proces

        chunk1 = new int[chunk];
        chunk2 = new int[chunk];
        nr_sum = new int[resL];

        fill(nr_sum, nr_sum + resL, 0); // init rez

        // send blocuri de dim chunk to procs
        for (int i = 1; i < numProcs; i++) {

            //citire numere
            for (int j = 0; j < chunk; j++) {
                if (j + (i - 1) * chunk < l1) {
                    f >> chunk1[j]; //citesc chunk
                } else {
                    chunk1[j] = 0; //0 daca depasesc lungimea
                }

                if (j + (i - 1) * chunk < l2) {
                    f2 >> chunk2[j];
                } else {
                    chunk2[j] = 0;
                }
            }

            // trimit catre procese ce am citit
            MPI_Send(chunk1, chunk, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(chunk2, chunk, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        f.close();
        f2.close();
    }

    // dimensiune catre toate procesele
    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //executie locala
    if (rank != 0) {

        int *chunk_1 = new int[chunk];
        int *chunk_2 = new int[chunk];
        int *chunk_result = new int[chunk];
        fill(chunk_result, chunk_result + chunk, 0); // init rez local

        // preiau datele de la procesul 0
        MPI_Recv(chunk_1, chunk, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(chunk_2, chunk, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //suma
        carry = 0;
        for (int i = 0; i < chunk; i++) {
            int number = chunk_1[i] + chunk_2[i] + carry;
            carry = number / 10;
            chunk_result[i] = number % 10;
        }

        // primesc carry de la procesele anterioare
        if (rank > 1) {
            int carry_recv; //carry primit
            MPI_Recv(&carry_recv, 1, MPI_INT, rank - 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //calcul propriu zis
            for (int i = 0; i < chunk; i++) {
                int number = chunk_result[i] + carry_recv;
                carry_recv = number / 10;
                if(carry_recv == 0)
                    break;
                chunk_result[i] = number % 10;
            }
            carry += carry_recv;
        }

        // se trimite carry la next proces
        if (rank < numProcs - 1) {
            MPI_Send(&carry, 1, MPI_INT, rank + 1, 2, MPI_COMM_WORLD);
        } else {
            // se trimite la procesul 0
            MPI_Send(&carry, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
        }

        // Trimite rezultatul calculat către procesul 0
        MPI_Send(chunk_result, chunk, MPI_INT, 0, 4, MPI_COMM_WORLD);

        delete[] chunk_1;
        delete[] chunk_2;
        delete[] chunk_result;
    }

    //primul proces
    if (rank == 0) {
        int *chunk_result = new int[chunk];

        //preiau si calculez suma finala
        for (int i = 1; i < numProcs; i++) {
            MPI_Recv(chunk_result, chunk, MPI_INT, i, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            copy(chunk_result, chunk_result + chunk, nr_sum + (i - 1) * chunk);
        }

        // preiau carry
        MPI_Recv(&carry, 1, MPI_INT, numProcs - 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (carry) {
            nr_sum[resL - 1] = carry;
        }

        saveToFile("sendSum.txt", nr_sum, carry ? resL : resL - 1);

        delete[] chunk1;
        delete[] chunk2;
        delete[] nr_sum;
        delete[] chunk_result;
    }

    MPI_Finalize();
}

//MPI_Gather(send_buffer, send_count, MPI_INT, recv_buffer, recv_count, MPI_INT, root_rank, MPI_COMM_WORLD);
void gatherMPI(int argc, char **argv) {

    //comunica carryul de la un proces la altul si la final isi comunica sumele partiale
    MPI_Init(&argc, &argv);
    //rank = 0,num_procs-1
    int rank, numProcs; //rank proc and no procs
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rank proc
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs); //no procs

    int l1, l2, rezL, chunk = 0;
    int *nr1 = nullptr;
    int *nr2 = nullptr;
    int *nr_sum = nullptr;

    auto t_start = chrono::steady_clock::now();

    //citesc numerele si dupa le voi impartii in chunkuri
    if (rank == 0) {
        ifstream f(argv[1]);
        ifstream f2(argv[2]);

        f >> l1;
        f2 >> l2;
        rezL = max(l1, l2) + 1; //lungime rezultat

        nr1 = new int[rezL];
        for (int i = 0; i < l1; i++) {
            f >> nr1[i];
        }
        f.close();

        for (int i = l1; i < rezL; i++) {
            nr1[i] = 0;  //0 pana ajung la lungimea maxima
        }

        nr2 = new int[rezL];
        for (int i = 0; i < l2; i++) {
            f2 >> nr2[i];
        }
        f2.close();
        for (int i = l2; i < rezL; i++) {
            nr2[i] = 0;
        }

        nr_sum = new int[rezL];

        //impart numerele in chunkuri egale
        chunk = (rezL - 1) / numProcs;

    }

    // trimit chunk catre toate procesele
    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *chunk1 = new int[chunk];
    int *chunk2 = new int[chunk];
    int *rez_chunk = new int[chunk];
    int carry = 0;

    //impart numarul in chunkuri
    MPI_Scatter(nr1, chunk, MPI_INT, chunk1, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(nr2, chunk, MPI_INT, chunk2, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    //fac suma propriu zisa
    for (size_t i = 0; i < chunk; i++) {
        int number = chunk1[i] + chunk2[i] + carry;
        if (number > 9)
            number = number % 10, carry = 1;
        else
            carry = 0;
        rez_chunk[i] = number;
    }

    //trimit carry la urmatoarul proces
    if (rank != 0) {
        int carry_recv;

        //carry de la procesul anterior
        MPI_Recv(&carry_recv, 1, MPI_INT, rank - 1, 111, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //suma
        for (size_t i = 0; i < chunk; i++) {
            int number = rez_chunk[i] + carry_recv;
            if (number > 9)
                number = number % 10, carry_recv = 1;
            else
                carry_recv = 0;

            rez_chunk[i] = number;
            if (!carry_recv)
                break;
        }

        //carry final
        carry += carry_recv;

        //trimit carry la urmatorul proces sau proc 0
        if (rank == numProcs - 1)
            MPI_Send(&carry, 1, MPI_INT, 0, 111, MPI_COMM_WORLD);
        else
            MPI_Send(&carry, 1, MPI_INT, rank + 1, 111, MPI_COMM_WORLD);
    }


    //procesul 0
    // primesc carry de la ultimul proces
    if (rank == 0) {
        MPI_Send(&carry, 1, MPI_INT, 1, 111, MPI_COMM_WORLD);
        MPI_Recv(&carry, 1, MPI_INT, numProcs - 1, 111, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    //adun rezultatele si preiau vectorul de suma
    MPI_Gather(rez_chunk, chunk, MPI_INT, nr_sum, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        auto t_final = chrono::steady_clock::now();
        auto diff = t_final - t_start;
        printf("%.4f", chrono::duration<double, milli>(diff).count());

        //adaug carry la final
        if (carry)
            nr_sum[rezL - 1] = carry, saveToFile("sumaGather.txt", nr_sum, rezL);
        else
            nr_sum[rezL - 1] = 0, saveToFile("sumaGather.txt", nr_sum, rezL - 1);

    }

    delete[] nr1;
    delete[] nr2;
    delete[] nr_sum;
    delete[] chunk1;
    delete[] chunk2;
    delete[] rez_chunk;
    MPI_Finalize();
}

int main() {
    const char *fakeArgv[] = {"mpi1", "Numar1.txt", "Numar2.txt"};
    int fakeArgc = 3;

    generateNumbers("Numar1.txt", 1000);
    generateNumbers("Numar2.txt", 1000);

//    sendRecvVar(fakeArgc, const_cast<char **>(fakeArgv));

    seq("Numar1.txt", "Numar2.txt");

//    gatherMPI(fakeArgc, const_cast<char **>(fakeArgv));

//    if (fileEq("Numar3.txt", "sumaGather.txt")) {
//        cout << "Files are equal" << endl;
//    } else {
//        cout << "Files are not equal" << endl;
//    }

    return 0;
}