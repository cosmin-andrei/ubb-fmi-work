package ro.ubbcluj.map.socialnetwork;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.controller.MessageAlert;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.service.CerereService;

import java.sql.SQLException;
import java.util.Collection;

public class RespondFriendController implements Observer {

    CerereService cerereService;
    private final ObservableList<Utilizator> model = FXCollections.observableArrayList();
    @FXML
    TableView<Utilizator> tableViewUser;
    private Stage stage;
    @FXML
    TableColumn<Utilizator, String> tableColumnPrenume;
    @FXML
    TableColumn<Utilizator, Long> tableColumnID;
    @FXML
    TableColumn<Utilizator, String>  tableColumnNume;
    private Long ID;

    @FXML
    public void initialize() {
        tableColumnID.setCellValueFactory(new PropertyValueFactory<>("id"));
        tableColumnNume.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnPrenume.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableViewUser.setItems(model);
    }

    public void setService(CerereService cerereService, Stage stage, Long ID) throws SQLException {
        this.cerereService = cerereService;
        this.stage = stage;
        this.ID = ID;
        cerereService.registerObserver(this);
        initModel();
    }

    private void initModel() throws SQLException {
        Collection<Utilizator> all = cerereService.pendingRequests(ID);
        model.setAll(all);
    }


    public void handleAccept(ActionEvent actionEvent) {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            try {
                cerereService.respondRequest(new Tuple<>(Long.valueOf(utilizator.getId().toString()), ID), "APPROVED");
                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Accepta cererea", "Cererea a fost acceptata!");
            } catch (SQLException e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }

    }

    @Override
    public void update() throws SQLException {
        initModel();
    }

    public void handleRefuz(ActionEvent actionEvent) {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            try {
                cerereService.respondRequest(new Tuple<>(Long.valueOf(utilizator.getId().toString()), ID), "");
                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Refuza cererea", "Cererea a fost refuzata!");
            } catch (SQLException e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }

    }

    public void handleCancel(ActionEvent actionEvent) {
        stage.close();
    }

}
