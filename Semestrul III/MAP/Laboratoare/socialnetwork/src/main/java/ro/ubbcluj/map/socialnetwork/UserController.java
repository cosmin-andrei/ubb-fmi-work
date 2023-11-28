package ro.ubbcluj.map.socialnetwork;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.controller.MessageAlert;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Collection;
import java.util.Observable;

public class UserController implements Observer {

    UtilizatorService userService;
    private final ObservableList<Utilizator> model = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableViewUser;
    @FXML
    TableColumn<Utilizator, String> tableColumnPrenume;
    @FXML
    TableColumn<Utilizator, Long> tableColumnID;
    @FXML
    TableColumn<Utilizator, String>  tableColumnNume;
    @FXML
    public void initialize() {
        tableColumnID.setCellValueFactory(new PropertyValueFactory<Utilizator, Long>("id"));
        tableColumnNume.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("firstName"));
        tableColumnPrenume.setCellValueFactory(new PropertyValueFactory<Utilizator, String>("lastName"));
        tableViewUser.setItems(model);
    }

    public void setService(UtilizatorService utilizatorService) throws SQLException {
        this.userService = utilizatorService;
        utilizatorService.registerObserver(this);
        initModel();
    }

    private void initModel() throws SQLException {
        Collection<Utilizator> all = (Collection<Utilizator>) userService.getAll();
        model.setAll(all);
    }

    public void handleAddUser(ActionEvent actionEvent) throws SQLException {
        showUserEditDialog(null);
    }

    public void handleDeleteUser(ActionEvent actionEvent) {

            Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
            if (utilizator != null) {
                try {
                    userService.stergeUtilizator(Long.valueOf(utilizator.getId().toString()));
                    MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Sterge utilizator", "Utilizator sters cu succes!");
                } catch (SQLException e) {
                    MessageAlert.showErrorMessage(null, e.getMessage());
                }
            } else {
                MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
            }


    }

    public void handleUpdateUser(ActionEvent actionEvent) throws SQLException {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            showUserEditDialog(utilizator);
            update();
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }
    }

    @Override
    public void update() throws SQLException {
        initModel();
    }

    private void showUserEditDialog(Utilizator utilizator) {

        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("edit-user-view.fxml"));

            AnchorPane root = (AnchorPane) loader.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Editeaza utilizatorul");
            dialogStage.initModality(Modality.WINDOW_MODAL);

            Scene scene = new Scene(root,600,300);
            dialogStage.setScene(scene);

            EditUserController editUserController = loader.getController();
            editUserController.setUtilizatorService(userService,dialogStage,utilizator);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}