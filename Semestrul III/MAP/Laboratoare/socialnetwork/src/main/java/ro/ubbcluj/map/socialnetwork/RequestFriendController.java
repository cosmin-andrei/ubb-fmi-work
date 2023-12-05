package ro.ubbcluj.map.socialnetwork;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.controller.MessageAlert;
import ro.ubbcluj.map.socialnetwork.domain.CererePrietenie;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.service.CerereService;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

import java.sql.SQLException;
import java.util.Collection;

public class RequestFriendController implements Observer {
    private CerereService cerereService;
    private UtilizatorService userService;
    private final ObservableList<Utilizator> model = FXCollections.observableArrayList();
    private Long ID;
    private Stage stage;
    @FXML
    private TextField textFieldIDPrieten;
    @FXML
    private Button buttonAdd;
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
        tableColumnID.setCellValueFactory(new PropertyValueFactory<>("id"));
        tableColumnNume.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnPrenume.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableViewUser.setItems(model);
    }

    public void setRequestService(UtilizatorService userService, CerereService cerereService, Stage stage, Long ID) throws SQLException {
        this.userService = userService;
        this.cerereService = cerereService;
        this.stage = stage;
        this.ID = ID;
        initModel();
    }

    private void initModel() throws SQLException {
        Collection<Utilizator> all = (Collection<Utilizator>) userService.getAll();
        model.setAll(all);
    }

    public void handleAdd(ActionEvent actionEvent) {
        try {
            String idPrieten = textFieldIDPrieten.getText().trim();

            if (idPrieten.isEmpty()) {
                MessageAlert.showErrorMessage(null, "Introduceti un ID de prieten.");
                return;
            }

            long idPrietenLong;
            try {
                idPrietenLong = Long.parseLong(idPrieten);
            } catch (NumberFormatException e) {
                MessageAlert.showErrorMessage(null, "ID-ul prietenului trebuie să fie un număr valid.");
                return;
            }

            if (ID.equals(idPrietenLong)) {
                MessageAlert.showErrorMessage(null, "Nu te poți împrieteni cu tine însuți.");
            } else {
                CererePrietenie cererePrietenie = new CererePrietenie();
                cererePrietenie.setId(new Tuple<>(ID, idPrietenLong));
                cererePrietenie.setStatus("PENDING");
                cerereService.addCerere(cererePrietenie);
                MessageAlert.showMessage(stage, Alert.AlertType.INFORMATION, "Cerere prietenie", "Cererea a fost trimisă cu succes.");
                stage.close();
            }
        } catch (Throwable t) {
//            t.printStackTrace(); // Afișează informații despre excepție în consolă
            MessageAlert.showErrorMessage(stage, "Eroare la trimiterea cererii: " + t.getMessage());
        }
    }

    @Override
    public void update() throws SQLException {
        initModel();
    }

}
