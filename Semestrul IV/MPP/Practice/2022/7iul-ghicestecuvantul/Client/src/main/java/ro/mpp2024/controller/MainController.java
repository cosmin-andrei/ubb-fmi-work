package ro.mpp2024.controller;

import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.*;
import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.util.List;

public class MainController implements IObserver {

    @FXML
    private Label lblPropuneri;
    @FXML
    private TextField txtModel;
    @FXML
    private Label lblScore;
    @FXML
    private TableView tblClasament;
    @FXML
    private TableColumn colPlayer;
    @FXML
    private TableColumn colScore;
    @FXML
    private TextField txtPlayer1;
    @FXML
    private TextField txtPlayer2;
    @FXML
    private Label lblPlayer1;
    @FXML
    private Label lblPlayer2;
    @FXML
    private Button bttnSend;
    @FXML
    private Label lblRunda;

//    ObservableList<Jucator> model = FXCollections.observableArrayList();

    private IServices server;
    private Jucator jucator;

    @FXML
    private Label lblPlayers;

    private List<Jucator> jucatori;

    private int runda;
    private List<Configuratie> configuratii;


    public MainController() {
    }

    public void setServer(IServices service) throws ServiceException {
        this.server = service;
        initmodel();
//        initialize();
    }

    private void initialize() {
    }

    private void initmodel() throws ServiceException {
        this.jucatori = server.getJucatori();
        for (Jucator jucator : jucatori) {
            lblPlayers.setText(lblPlayers.getText() + jucator.getId() + " ");
        }

        lblPropuneri.setText("Propuneri: " + server.getPropuneri());
        this.runda=0;
    }

    void logout() {
        try {
            server.logout(jucator, this);
        } catch (ServiceException e) {
            System.out.println("Logout error " + e);
        }

    }

    public void handleLogout(ActionEvent actionEvent) {
        logout();
        ((Node) (actionEvent.getSource())).getScene().getWindow().hide();
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void handleStart(ActionEvent actionEvent) throws ServiceException {
        if (server.getJucatori().size() == 3){
            gameStart();
        }
        else{
            MessageAlert.showErrorMessage(null, "Nu sunt suficienti jucatori");
        }
    }

    private void gameStart() throws ServiceException {
        runda = 1;
        lblRunda.setText("Runda curenta: " + runda);

        jucatori.remove(jucator);

        lblPlayer1.setText("Player 1: " + jucatori.getFirst().getId() );
        lblPlayer2.setText("Player 2: " + jucatori.getLast().getId()+ server.getConfiguratie(jucatori.getLast().getId()).getModel().length());

    }

    public void handleSend(ActionEvent actionEvent) {
    }

    public void handleTrimite(ActionEvent actionEvent) {
        try {
            Configuratie configuratie = new Configuratie(txtModel.getText(), jucator.getId());
            configuratie.setId(3L);
            server.saveConfiguration(configuratie);
//            configuratii.add(configuratie);
        } catch (ServiceException e) {
            throw new RuntimeException(e);
        }
    }
}
