package parallel;

import parallel.ConvThreads.ConvColThread;

public class Col_Conv {
    int N, M, n, p;
    int[][] F, C;

    public Col_Conv(int n, int m, int n1, int p, int[][] f, int[][] c) {
        N = n;
        M = m;
        this.n = n1;
        this.p = p;
        F = f;
        C = c;

    }

    public int[][] run() {
        int[][] result = new int[N][M];
        Thread[] threads = new Thread[p];

        int start = 0;
        int end = -1;
        int step = M / p;
        int rest = M % p;

        for (int i = 0; i < p; i++) {
            end = start + step;
            if (rest > 0) {
                end++;
                rest--;
            }

            threads[i] = new ConvColThread(start, end, n, N, M, F, C, result);
            threads[i].start();
            start = end;
        }

        for (int i = 0; i < p; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        return result;
    }
}
