package sequential;

public class Convolutie_Secventiala {

    int N, M, n, p;
    int[][] F, C;

    public Convolutie_Secventiala(int n, int m, int n1, int p, int[][] f, int[][] c) {
        N = n;
        M = m;
        this.n = n1;
        this.p = p;
        F = f;
        C = c;
    }

    public int[][] run() {
        int[][] result = new int[N][M];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                result[i][j] = convolute(i, j);

        return result;
    }

    private int convolute(int i, int j) {
        int sum = 0;
        for (int i1 = 0; i1 < n; i1++)
            for (int j1 = 0; j1 < n; j1++)
                if (i + i1 - n / 2 >= 0 && i + i1 - n / 2 < N && j + j1 - n / 2 >= 0 && j + j1 - n / 2 < M)
                    sum += F[i + i1 - n / 2][j + j1 - n / 2] * C[i1][j1];

        return sum;
    }
}
