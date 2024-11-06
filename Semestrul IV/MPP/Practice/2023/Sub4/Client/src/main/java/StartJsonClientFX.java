import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2024.controller.LoginController;
import ro.mpp2024.networking.jsonprotocol.ServicesJsonProxy;
import ro.mpp2024.service.IServices;

import java.io.IOException;
import java.util.Properties;


public class StartJsonClientFX extends Application{

    private static int defaultPort = 55555;
    private static String defaultServer = "localhost";
    private static final Logger logger= LogManager.getLogger();

    public void start(Stage primaryStage) throws Exception {

        System.out.println("In start");
        Properties clientProps = new Properties();
        try {
            clientProps.load(StartJsonClientFX.class.getResourceAsStream("/client.properties"));
            logger.info("Client properties set. ");
            System.out.println("Client properties set. ");
            clientProps.list(System.out);
        } catch (IOException e) {
            logger.error(e);
            System.err.println("Cannot find client.properties " + e);
            return;
        }
        String serverIP = clientProps.getProperty("server.host", defaultServer);
        int serverPort = defaultPort;

        try {
            serverPort = Integer.parseInt(clientProps.getProperty("server.port"));
        } catch (NumberFormatException ex) {
            logger.error("Wrong port number " + ex.getMessage());
            logger.error("Using default port: " + defaultPort);
            System.err.println("Wrong port number " + ex.getMessage());
            System.out.println("Using default port: " + defaultPort);
        }

        logger.info("Using server IP " + serverIP);
        logger.info("Using server port " + serverPort);
        System.out.println("Using server IP " + serverIP);
        System.out.println("Using server port " + serverPort);

        IServices server = new ServicesJsonProxy(serverIP, serverPort);


        FXMLLoader loginLoader = new FXMLLoader();
        loginLoader.setLocation(getClass().getResource("login-view.fxml"));

        AnchorPane loginVBox = loginLoader.load();
        LoginController loginController = loginLoader.getController();

        Scene scene = new Scene(loginVBox);

        primaryStage.setTitle("Joc");
        primaryStage.setScene(scene);

        loginController.setServer(server);

        primaryStage.show();


    }

    public static void main(String[] args) {
        launch(args);
    }

}
