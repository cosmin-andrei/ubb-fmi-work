package ro.mpp2024.client;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import ro.mpp2024.IServices;
import ro.mpp2024.Jucator;
import ro.mpp2024.ServiceException;

import java.io.IOException;

public class LoginController {

    private IServices server;
    private Jucator jucator;
    private MainController mainController;

    @FXML
    private TextField txtAlias;

    public void setServer(IServices server) {
        this.server = server;
    }

    public void handleLogin(ActionEvent actionEvent) {
        if (txtAlias.getText().isEmpty()) {
            MessageAlert.showErrorMessage(null, "Introdu un alias");
        } else {
            String alias = txtAlias.getText();
            Jucator jucator = new Jucator(alias);
            try {

                FXMLLoader mainLoader = new FXMLLoader();
                mainLoader.setLocation(getClass().getResource("/main-view.fxml"));
                AnchorPane root = mainLoader.load();

                MainController mainController = mainLoader.getController();
                server.login(jucator, mainController);
                System.out.println("Login successful");

                mainController.setJucator(jucator);
                mainController.setServer(server);

                Stage primaryStage = new Stage();
                primaryStage.setTitle("Main");
                primaryStage.initModality(Modality.WINDOW_MODAL);

                Scene scene = new Scene(root);
                primaryStage.setScene(scene);

                primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                    @Override
                    public void handle(WindowEvent event) {
                        mainController.logout();
                        System.exit(0);
                    }
                });

                primaryStage.show();

            } catch (ServiceException e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

}
