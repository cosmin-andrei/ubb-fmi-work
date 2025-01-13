#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

MPI_Request recv_request[10];

int main1(int argc, char **argv) {

    int namelen, myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    //printf("Process %d / %d  : Hello world\n", myid, numprocs);

    char *mymessage = new char[50];
    strcpy_s(mymessage, 50, "Hello from ");

    char *sirTotal = new char[50 * numprocs];
    sirTotal[0] = '\0';

    if (myid == 0) {
        strcat_s(mymessage, 50, "0");
        strcat_s(sirTotal, 50, mymessage);
        MPI_Status status;
        for (int i = 1; i < numprocs; i++) {
            MPI_Recv(mymessage, 50, MPI_CHAR, i, 111, MPI_COMM_WORLD, &status);
            //printf("STATUS SOURCE %d\n", status.MPI_SOURCE);
            strcat_s(sirTotal, 50, mymessage);
        }
        printf("%s\n", sirTotal);
    } else {
        char *buf = new char[10];
        _itoa_s(myid, buf, 10, 10);
        strcat_s(mymessage, 50, buf);
        MPI_Send(mymessage, strlen(mymessage) + 1, MPI_CHAR, 0, 111, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

int main2(int argc, char **argv) {

    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    //printf("Process %d / %d  : Hello world\n", myid, numprocs);

    char **mymessage = new char *[numprocs];
    for (int i = 0; i < numprocs; i++) {
        mymessage[i] = new char[50];
        strcpy_s(mymessage[i], 50, "Hello from ");

    }
    char *sirTotal = new char[50 * numprocs];
    sirTotal[0] = '\0';

    if (myid == 0) {
        strcat_s(mymessage[0], 50, "0");
        strcat_s(sirTotal, 50, mymessage[0]);
        MPI_Status status;
        MPI_Request *request = new MPI_Request[numprocs];
        for (int i = 1; i < numprocs; i++) {
            //astept mesaj de la 1,2,3 si trece mai departe
            MPI_Irecv(mymessage[i], 50, MPI_CHAR, i, 111, MPI_COMM_WORLD, &request[i]);
        }
        int contor = 0;
        int *flag = new int[numprocs];
        while (contor < numprocs - 1) {
            for (int i = 1; i < numprocs; i++) {
                MPI_Test(&request[i], &flag[i], &status);
                if (flag[i]) {
                    strcat_s(sirTotal, 50 * numprocs, mymessage[i]);
                    contor++;
                }
            }
        }
        printf("%s\n", sirTotal);

        MPI_Waitall(numprocs - 1, request + 1, MPI_STATUS_IGNORE);

    } else {
        char *buf = new char[10];
        MPI_Request *req = new MPI_Request;
        _itoa_s(myid, buf, 10, 10);
        strcat_s(mymessage[myid], 50, buf);
        MPI_Isend(mymessage[myid], strlen(mymessage[myid]) + 1, MPI_CHAR, 0, 111, MPI_COMM_WORLD, req);
        MPI_Wait(req, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();
    return 0;
}

int main3(int argc, char **argv) {

    const int n = 100;
    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    //printf("Process %d / %d  : Hello world\n", myid, numprocs);

    char **mymessage = new char *[numprocs];
    for (int i = 0; i < numprocs; i++) {
        mymessage[i] = new char[50];
        strcpy_s(mymessage[i], 50, "Hello from ");

    }
    char *sirTotal = new char[50 * numprocs];
    sirTotal[0] = '\0';

    int cate = n / numprocs;
    if (myid == 0) {
        int *a = new int[n];
        int *b = new int[n];
        int *c = new int[n];

        for (size_t i = 0; i < n; i++) {
            a[i] = b[i] = i;
        }

        for (size_t i = 1; i < numprocs; i++) {
            MPI_Send(a + i * cate, cate, MPI_INT, i, 111, MPI_COMM_WORLD);
        }

        for (size_t i = 1; i < numprocs; i++) {
            MPI_Send(b + i * cate, cate, MPI_INT, i, 222, MPI_COMM_WORLD);
        }

        for (size_t i = 0; i < cate; i++) {
            c[i] = a[i] + b[i];
        }

        for (size_t i = 1; i < numprocs; i++) {
            MPI_Recv(c + i * cate, cate, MPI_INT, i, 333, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (size_t i = 0; i < n; i++) {
            printf("%d ", c[i]);
            if (c[i] != 2 * i) {
                printf("EROARE\n");
                break;
            }
        }

    } else {
        int *a = new int[cate];
        int *b = new int[cate];
        int *c = new int[cate];
        MPI_Recv(a, cate, MPI_INT, 0, 111, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, cate, MPI_INT, 0, 222, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (size_t i = 0; i < cate; i++) {
            c[i] = a[i] + b[i];
        }

        MPI_Send(c, cate, MPI_INT, 0, 333, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


int main(int argc, char **argv) {

    const int n = 100;
    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    //printf("Process %d / %d  : Hello world\n", myid, numprocs);

    char **mymessage = new char *[numprocs];
    for (int i = 0; i < numprocs; i++) {
        mymessage[i] = new char[50];
        strcpy_s(mymessage[i], 50, "Hello from ");

    }
    char *sirTotal = new char[50 * numprocs];
    sirTotal[0] = '\0';
    int *a = new int[n];
    int *b = new int[n];
    int *c = new int[n];
    int cate = n / numprocs;
    int *aa = new int[cate];
    int *bb = new int[cate];
    int *cc = new int[cate];

    if (myid == 0) {
        for (size_t i = 0; i < n; i++) {
            a[i] = b[i] = i;
        }
    }

    MPI_Scatter(a, cate, MPI_INT, aa, cate, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, cate, MPI_INT, bb, cate, MPI_INT, 0, MPI_COMM_WORLD);

    for (size_t i = 0; i < cate; i++) {
        cc[i] = aa[i] + bb[i];
    }

    MPI_Gather(cc, cate, MPI_INT, c, cate, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < n; i++) {
        printf("%d ", c[i]);
        if (c[i] != 2 * i) {
            printf("EROARE\n");
            break;
        }
    }

    MPI_Finalize();

    return 0;
}