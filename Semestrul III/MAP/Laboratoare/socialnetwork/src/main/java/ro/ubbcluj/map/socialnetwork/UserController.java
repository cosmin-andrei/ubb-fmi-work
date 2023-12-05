package ro.ubbcluj.map.socialnetwork;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.controller.MessageAlert;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.service.CerereService;
import ro.ubbcluj.map.socialnetwork.service.MessageService;
import ro.ubbcluj.map.socialnetwork.service.PrietenieService;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Collection;

public class UserController implements Observer {

    UtilizatorService userService;
    CerereService cerereService;
    PrietenieService prietenieService;
    MessageService messageService;
    private final ObservableList<Utilizator> model = FXCollections.observableArrayList();
    private final ObservableList<Utilizator> modelPrietenie = FXCollections.observableArrayList();


    @FXML
    TableView<Utilizator> tableViewUser;
    @FXML
    TableView<Utilizator> viewTableFriends;
    @FXML
    TableColumn<Utilizator, String> tableColumnPrenume;
    @FXML
    TableColumn<Utilizator, Long> tableColumnID;
    @FXML
    TableColumn<Utilizator, String>  tableColumnNume;

    @FXML
    TableColumn<Utilizator, String> lastNameColumn;
    @FXML
    TableColumn<Utilizator, Long> idColumn;
    @FXML
    TableColumn<Utilizator, String>  firstNameColumn;
    @FXML
    public void initialize() {
        tableColumnID.setCellValueFactory(new PropertyValueFactory<>("id"));
        tableColumnNume.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnPrenume.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableViewUser.setItems(model);
    }


    public void setService(UtilizatorService utilizatorService, CerereService cerereService, PrietenieService prietenieService, MessageService messageService) throws SQLException {
        this.cerereService = cerereService;
        this.userService = utilizatorService;
        this.prietenieService = prietenieService;
        this.messageService = messageService;
        utilizatorService.registerObserver(this);
        initModel();
    }

    private void initModel() throws SQLException {
        Collection<Utilizator> all = (Collection<Utilizator>) userService.getAll();
        model.setAll(all);
    }

    public void handleAddUser(ActionEvent actionEvent) {
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

            dialogStage.setResizable(true);
            Scene scene = new Scene(root,600,300);
            dialogStage.setScene(scene);

            EditUserController editUserController = loader.getController();
            editUserController.setUtilizatorService(userService,dialogStage,utilizator);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    @FXML
    public void handleCerePrietenia(ActionEvent actionEvent) {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            Long ID = utilizator.getId();
            showRequestFriendshipDialog(ID);
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }
    }

    private void showRequestFriendshipDialog(Long ID) {


        try {
            FXMLLoader loader1 = new FXMLLoader();
            loader1.setLocation(getClass().getResource("request-friendship.fxml"));

            AnchorPane root1 = (AnchorPane) loader1.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Cere prietenia");
            dialogStage.initModality(Modality.WINDOW_MODAL);
            dialogStage.setResizable(true);
            Scene scene = new Scene(root1,600,300);
            dialogStage.setScene(scene);

            RequestFriendController requestFriendController = loader1.getController();
            requestFriendController.setRequestService(userService,cerereService,dialogStage,ID);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void handleRaspundePrietenie(ActionEvent actionEvent) {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            Long ID = utilizator.getId();
            showRespondFriendshipDialog(ID);
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }
    }

    private void showRespondFriendshipDialog(Long ID) {


        try {
            FXMLLoader loader1 = new FXMLLoader();
            loader1.setLocation(getClass().getResource("view-requests.fxml"));

            AnchorPane root1 = (AnchorPane) loader1.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Vezi cereri prietenie");
            dialogStage.initModality(Modality.WINDOW_MODAL);

            Scene scene = new Scene(root1,600,300);
            dialogStage.setResizable(true);
            dialogStage.setScene(scene);

            RespondFriendController respondFriendController = loader1.getController();
            respondFriendController.setService(cerereService, dialogStage, ID);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private void initModelPrietenie(Collection<Utilizator> prieteni) {
        modelPrietenie.setAll(prieteni);
        viewTableFriends.setItems(modelPrietenie);
    }

    @FXML
    private void initializePrietenie() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        viewTableFriends.setItems(model);
    }
    public void handlePrieteni(ActionEvent actionEvent) {
        initializePrietenie();
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            try {

                Collection<Utilizator> prieteni = prietenieService.getPrieteniById(utilizator.getId());
               initModelPrietenie(prieteni);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }
    }


    public void handleMesaje(ActionEvent actionEvent) {
        Utilizator utilizator = tableViewUser.getSelectionModel().getSelectedItem();
        if (utilizator != null) {
            Long ID = utilizator.getId();
            showConversationDialog(ID);
        } else {
            MessageAlert.showErrorMessage(null, "Niciun utilizator selectat.");
        }
    }

    private void showConversationDialog(Long id) {
        try {
            FXMLLoader loader1 = new FXMLLoader();
            loader1.setLocation(getClass().getResource("message-view.fxml"));

            AnchorPane root1 = (AnchorPane) loader1.load();

            Stage dialogStage = new Stage();
            dialogStage.setTitle("Conversatie");
            dialogStage.initModality(Modality.WINDOW_MODAL);

            Scene scene = new Scene(root1,600,300);
            dialogStage.setResizable(true);
            dialogStage.setScene(scene);

            MessageController messageController = loader1.getController();
            messageController.setService(messageService, dialogStage, id);

            dialogStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}