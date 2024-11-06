package parallel.ConvThreads;

public class ConvColThread extends Thread {

    int start, end, N, M, n;

    int[][] F, C, result;

    public ConvColThread(int start, int end, int n, int N, int M, int[][] F, int[][] C, int[][] result) {
        this.start = start;
        this.end = end;
        this.N = N;
        this.M = M;
        this.n = n;
        this.F = F;
        this.C = C;
        this.result = result;
    }

    public void run() {
        for (int j = start; j < end; j++)
            for (int i = 0; i < N; i++)
                result[i][j] = convolute(i, j);

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
