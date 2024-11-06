package ro.mpp2024;

import ro.mpp2024.networking.utils.AbstractServer;
import ro.mpp2024.networking.utils.JsonConcurrentServer;
import ro.mpp2024.repository.ConfiguratieRepo;
import ro.mpp2024.repository.JucatorRepo;
import ro.mpp2024.repository.interfaces.ConfiguratieRepoInterface;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;
import ro.mpp2024.server.ServicesImpl;
import ro.mpp2024.service.IServices;

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

        JucatorRepoInterface voluntarRepo = new JucatorRepo(serverProps);
        ConfiguratieRepoInterface configuratieRepo = new ConfiguratieRepo();
        IServices service = new ServicesImpl(voluntarRepo, configuratieRepo);
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
