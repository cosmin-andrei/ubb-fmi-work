import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Server{

    public static void main(String[] args) throws IOException {
        ServerSocket s = new ServerSocket(1234);
        String sir;

        while(true){
            Socket c = s.accept();
            System.out.println("Clientul s-a conectat!");
            sir = request.getRequest();

            Pattern pattern = Pattern.compile("\s");
            Matcher matcher = pattern.matcher(sir);


            c.close();
        }
    }

}