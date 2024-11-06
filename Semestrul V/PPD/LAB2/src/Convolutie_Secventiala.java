public class Convolutie_Secventiala {
    int N, M, n, p;
    int[][] F;
    int[][] C;

    public Convolutie_Secventiala(int N, int M, int n, int p, int[][] F, int[][] C) {
        this.N = N;
        this.M = M;
        this.n = n;
        this.p = p;
        this.F = F;
        this.C = C;
    }

    public void run() {
        int[] prev = new int[M];
        int[] curr = new int[M];

        System.arraycopy(F[0], 0, prev, 0, M);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int sum = convolute(i, j, prev);
                curr[j] = sum;
            }
            // copy curr line pt a avea val init
            System.arraycopy(F[i], 0, prev, 0, M);

            //rezultatul in matrice
            System.arraycopy(curr, 0, F[i], 0, M);
        }
    }

    private int convolute(int i, int j, int[] prev) {
        int sum = 0;
        for (int i1 = 0; i1 < n; i1++) {
            for (int j1 = 0; j1 < n; j1++) {
                int indexI = i + i1 - n / 2;
                int indexJ = j + j1 - n / 2;
                if (indexI < 0) indexI = 0;
                if (indexJ < 0) indexJ = 0;
                if (indexI >= N) indexI = N - 1;
                if (indexJ >= M) indexJ = M - 1;
                if (i1 == 0) {
                    sum += prev[indexJ] * C[i1][j1];
                } else {
                    sum += F[indexI][indexJ] * C[i1][j1];
                }
            }
        }
        return sum;
    }
}
