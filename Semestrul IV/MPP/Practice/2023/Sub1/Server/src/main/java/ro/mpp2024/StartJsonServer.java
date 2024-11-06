package ro.mpp2024;


import ro.mpp2024.IRepositories.IConfiguratieRepo;
import ro.mpp2024.IRepositories.IJucatorRepo;
import ro.mpp2024.IRepositories.IRundaCurentaRepo;
import ro.mpp2024.IRepositories.IRundaRepo;
import ro.mpp2024.server.ServicesImpl;
import ro.mpp2024.utils.AbstractServer;
import ro.mpp2024.utils.JsonConcurrentServer;


import java.io.IOException;
import java.rmi.ServerException;
import java.util.Properties;

public class StartJsonServer {
    private static int defaultPort=55555;
    public static void main(String[] args) {

        Properties serverProps=new Properties();
        try {
            serverProps.load(StartJsonServer.class.getResourceAsStream("/server.properties"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find properties "+e);
            return;
        }

        IConfiguratieRepo configuratieRepo = new ConfiguratieRepository();
        IJucatorRepo jucatorRepo = new JucatorRepository(serverProps);
        IRundaCurentaRepo rundaCurentaRepo = new RundaCurentaRepository(serverProps);
        IRundaRepo rundaRepo = new RundaRepository(serverProps);

        IServices service = new ServicesImpl(jucatorRepo, configuratieRepo, rundaCurentaRepo, rundaRepo);

        int ServerPort=defaultPort;
        try {
            ServerPort = Integer.parseInt(serverProps.getProperty("server.port"));
        }catch (NumberFormatException nef){
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        System.out.println("Starting server on port: "+ServerPort);
        AbstractServer server = new JsonConcurrentServer(ServerPort, service);
        try {
            server.start();
        } catch (ServerException e) {
            System.err.println("Error starting the server" + e.getMessage());
        }
    }
}
