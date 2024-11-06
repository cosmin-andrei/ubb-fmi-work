package ro.mpp2024.controller;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.io.IOException;

public class LoginController {

    private IServices server;
    private MainController mainController;

    @FXML
    private TextField lblUsername;

    public void setServer(IServices server) {
        this.server = server;
    }

    public void handleLogin(ActionEvent actionEvent) throws ServiceException {
        if (lblUsername.getText().isEmpty()) {
            MessageAlert.showErrorMessage(null, "Introdu un alias");
        } else {

            String username = lblUsername.getText();
            Jucator jucator = new Jucator(username);

            try {

                FXMLLoader userLoader = new FXMLLoader();
                userLoader.setLocation(getClass().getResource("/main-view.fxml"));
                AnchorPane root = userLoader.load();

                MainController mainController = userLoader.getController();
                server.login(jucator, mainController);

                mainController.setJucator(jucator);
                mainController.setServer(server);

                Stage userStage = new Stage();
                userStage.setTitle("Jucator: " + jucator.getId());
                userStage.initModality(Modality.WINDOW_MODAL);
                Scene scene = new Scene(root);
                userStage.setScene(scene);

                userStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                    @Override
                    public void handle(WindowEvent event) {
                        mainController.logout();
                        System.exit(0);
                    }
                });

                userStage.show();

                ((Node) (actionEvent.getSource())).getScene().getWindow().hide();

            } catch (ServiceException e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

        }
    }



}

