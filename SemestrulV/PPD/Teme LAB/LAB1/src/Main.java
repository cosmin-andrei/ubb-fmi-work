import parallel.Col_Conv;
import parallel.Line_Conv;
import sequential.Convolutie_Secventiala;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    static int[][] F;
    static int[][] C;

    // N - no. lines F
    // M - no. cols F
    // n - dim. C
    static int N, M, n, p, offset;

    static int[][] result;

    public static void main(String[] args) throws FileNotFoundException {

        read_data();

        long start = System.nanoTime();
        if (args.length < 1) {
            System.out.println("Usage: java Main <no_of_threads>");
            return;
        }

        p = Integer.parseInt(args[0]);
//        p = 1;
        System.out.println("Number of threads: " + p);


//        int type = Integer.parseInt(args[1]);
        int type = 1;
        System.out.println("Type: " + type);


        if (type == 1) {
            System.out.println("Type 1");
            Convolutie_Secventiala p1 = new Convolutie_Secventiala(N, M, n, p, F, C);
            result = p1.run();
        } else if (type == 2) {
            System.out.println("Type 2");
            Col_Conv p2 = new Col_Conv(N, M, n, p, F, C);
            result = p2.run();
        } else if (type == 3) {
            System.out.println("Type 3");
            Line_Conv p3 = new Line_Conv(N, M, n, p, F, C);
            result = p3.run();
        } else {
            System.out.println("Tip invalid");
            return;
        }


        //output result in output.txt
        try (PrintWriter writer = new PrintWriter("D:\\Facultate\\ubb-fmi-work\\Semestrul V\\PPD\\LAB1\\data\\output.txt")) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    writer.print(result[i][j] + " ");
                }
                writer.println();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println((double) (endTime - start) / 1E6);

    }

    private static void read_data() throws FileNotFoundException {

        Scanner reader = new Scanner(new File("D:\\Facultate\\ubb-fmi-work\\Semestrul V\\PPD\\LAB1\\data\\date.txt"));

        N = reader.nextInt();
        M = reader.nextInt();
        F = new int[N][M];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                F[i][j] = reader.nextInt();

        result = new int[N][M];

        n = reader.nextInt();
        C = new int[n][n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = reader.nextInt();

        reader.close();

    }

}

