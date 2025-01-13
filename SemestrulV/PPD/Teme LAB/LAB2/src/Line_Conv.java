import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Line_Conv {
    int N, M, n, p;
    int[][] F;
    int[][] C;
    CyclicBarrier barrier;

    public Line_Conv(int N, int M, int n, int p, int[][] F, int[][] C) {
        this.N = N;
        this.M = M;
        this.n = n;
        this.p = p;
        this.F = F;
        this.C = C;
    }

    public void run() throws InterruptedException {
        Thread[] threads = new Thread[p];

        barrier = new CyclicBarrier(p);

        int startRow = 0;
        int endRow;
        int rowsPerThread = N / p;
        int remainingRows = N % p;


        for (int k = 0; k < p; ++k) {
            endRow = startRow + rowsPerThread;
            if (remainingRows > 0) {
                endRow++;
                remainingRows--;
            }

            threads[k] = new LineThread(startRow, endRow);
            threads[k].start();
            startRow = endRow;
        }

        for (int i = 0; i < p; ++i)
            threads[i].join();
    }

    class LineThread extends Thread {
        final private int start, end;

        public LineThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public void run() {
            int[] up = new int[M];
            int[] down = new int[M];
            int[] prev = new int[M];
            int[] curr = new int[M];

            // vecinul - e in int matricei sau e bordura matricei
            if (start > 0)
                System.arraycopy(F[start - 1], 0, up, 0, M);
            else
                System.arraycopy(F[0], 0, up, 0, M);

            // vecinul de jos - e in int matricei sau e bordura matricei
            if (end < N)
                System.arraycopy(F[end], 0, down, 0, M);
            else
                System.arraycopy(F[N - 1], 0, down, 0, M);

            System.arraycopy(F[start], 0, prev, 0, M);
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                throw new RuntimeException(e);
            }

            for (int i = start; i < end; ++i) {
                for (int j = 0; j < M; ++j) {
                    convoluted(i, j, up, down, prev, curr);
                }

                //copie linie curenta cu val init
                System.arraycopy(F[i], 0, prev, 0, M);

                //copie rezultat in mat
                System.arraycopy(curr, 0, F[i], 0, M);
            }

        }

        private void convoluted(int i, int j, int[] up, int[] down, int[] prev, int[] curr) {
            int sum = 0;
            for (int i1 = 0; i1 < n; i1++) {
                for (int j1 = 0; j1 < n; j1++) {

                    int xI = i + i1 - n / 2;
                    int xJ = j + j1 - n / 2;

                    if (xI < 0) xI = 0;
                    if (xJ < 0) xJ = 0;
                    if (xI >= N) xI = N - 1;
                    if (xJ >= M) xJ = M - 1;

                    //prima linie a th
                    if (i1 == 0 && i == start) {
                        sum += up[xJ] * C[i1][j1];
                    } else if (i1 == n - 1 && i == end - 1) { //ultima linie th
                        sum += down[xJ] * C[i1][j1];
                    } else {
                        if (i1 == 0) {
                            sum += prev[xJ] * C[i1][j1];
                        } else {
                            sum += F[xI][xJ] * C[i1][j1];
                        }
                    }
                }
            }
            curr[j] = sum;
        }
    }
}