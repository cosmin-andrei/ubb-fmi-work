import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    static int[][] F;
    static int[][] C;
    static int[][] F_copy;

    // N - no. lines F
    // M - no. cols F
    // n - dim. C
    static int N;
    static int M;
    static int n;
    static int p;


    public static void main(String[] args) throws FileNotFoundException, InterruptedException {

        read_data();

        long start = System.nanoTime();
        if (args.length < 1) {
            System.out.println("Usage: java Main <no_of_threads>");
            return;
        }

        p = Integer.parseInt(args[0]);
        System.out.println("Number of threads: " + p);
        System.out.println(p);

        Convolutie_Secventiala p1 = new Convolutie_Secventiala(N, M, n, p, F_copy, C);
        p1.run();

//        Line_Conv p2 = new Line_Conv(N, M, n, p, F, C);
//        p2.run();


        //output result in output.txt
        try (PrintWriter writer = new PrintWriter("D:\\Facultate\\ubb-fmi-work\\Semestrul V\\PPD\\LAB2\\data\\output.txt")) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    writer.print(F[i][j] + " ");
                }
                writer.println();
            }
        } catch (FileNotFoundException e) {
            System.err.println("Error writing output file: " + e.getMessage());
        }

        long endTime = System.nanoTime();
        System.out.println((double) (endTime - start) / 1E6);

//        if (compareMatrices(F, F_copy)) {
//            System.out.println("1");
//        } else {
//            System.out.println("0");
//        }

    }



    private static void read_data() throws FileNotFoundException {

        Scanner reader = new Scanner(new File("D:\\Facultate\\ubb-fmi-work\\Semestrul V\\PPD\\LAB2\\data\\date.txt"));

        N = reader.nextInt();
        M = reader.nextInt();
        F = new int[N][M];
        F_copy = new int[N][M];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
//                F[i][j] = reader.nextInt();
//                F_copy[i][j] = F[i][j];
            }

        n = reader.nextInt();
        C = new int[n][n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = reader.nextInt();

        reader.close();

    }

    private static boolean compareMatrices(int[][] mat1, int[][] mat2) {
        if (mat1.length != mat2.length || mat1[0].length != mat2[0].length) {
            return false;
        }

        for (int i = 0; i < mat1.length; i++) {
            for (int j = 0; j < mat1[0].length; j++) {
                if (mat1[i][j] != mat2[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

}

