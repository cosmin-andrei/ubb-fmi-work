import java.io.*;
import java.net.Socket;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Client {
    public static void main(String[] args) throws Exception {

        Socket c = new Socket("127.0.0.1", 1234);
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        String str = reader.readLine();
        System.out.println(str);

        DataInputStream socketIn = new DataInputStream(c.getInputStream());
        DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

        int len = str.length();
        socketOut.writeInt(len);
        socketOut.writeUTF(str);
        socketOut.flush();

        int rez=socketIn.readUnsignedShort();
        System.out.println("rezultat = " + rez);


        reader.close();
        c.close();

    }
}