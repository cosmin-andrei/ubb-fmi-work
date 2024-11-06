package ro.mpp2024;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2024.networking.utils.AbstractServer;
import ro.mpp2024.networking.utils.JsonConcurrentServer;
import ro.mpp2024.repository.JucatorRepo;
import ro.mpp2024.repository.RundaRepo;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;
import ro.mpp2024.server.ServicesImpl;
import ro.mpp2024.service.IServices;

import java.io.IOException;
import java.rmi.ServerException;
import java.util.Properties;

public class StartJsonServer {
    private static int defaultPort=55555;
    private static final Logger logger= LogManager.getLogger();
    public static void main(String[] args) {

        Properties serverProps=new Properties();
        try {
            serverProps.load(StartJsonServer.class.getResourceAsStream("/server.properties"));
            logger.info("Server properties set. ");
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            logger.error(e);
            System.err.println("Cannot find properties "+e);
            return;
        }

        JucatorRepoInterface voluntarRepo = new JucatorRepo(serverProps);
        RundaRepoInterface rundaRepo = new RundaRepo();
        IServices service = new ServicesImpl(voluntarRepo, rundaRepo);
        int ServerPort=defaultPort;
        try {
            ServerPort = Integer.parseInt(serverProps.getProperty("server.port"));
        }catch (NumberFormatException nef){
            logger.error("Wrong  Port Number"+nef.getMessage());
            logger.error("Using default port "+defaultPort);
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        logger.info("Starting server on port: "+ServerPort);
        System.out.println("Starting server on port: "+ServerPort);
        AbstractServer server = new JsonConcurrentServer(ServerPort, service);
        try {
            server.start();
        } catch (ServerException e) {
            logger.error("Error starting the server"+e.getMessage());
            System.err.println("Error starting the server" + e.getMessage());
        }
    }
}
