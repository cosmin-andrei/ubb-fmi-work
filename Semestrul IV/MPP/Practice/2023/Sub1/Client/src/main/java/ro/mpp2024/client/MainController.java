package ro.mpp2024.client;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import ro.mpp2024.*;

public class MainController implements IObserver {

    private IServices server;
    private Jucator jucator;
    private Integer row;
    private Integer col;
    private RundaCurenta runda;
    private Boolean gameOver;

    @FXML
    private Label lbl11;
    @FXML
    private Label lbl12;
    @FXML
    private Label lbl13;
    @FXML
    private Label lbl14;
    @FXML
    private Label lbl21;
    @FXML
    private Label lbl22;
    @FXML
    private Label lbl23;
    @FXML
    private Label lbl24;
    @FXML
    private Label lbl31;
    @FXML
    private Label lbl32;
    @FXML
    private Label lbl33;
    @FXML
    private Label lbl34;
    @FXML
    private Label lbl41;
    @FXML
    private Label lbl42;
    @FXML
    private Label lbl43;
    @FXML
    private Label lbl44;

    @FXML
    private TextField lblIndiciu;
    @FXML
    private TextField lblNrIncercari;
    @FXML
    private TextField lblDistanta;

    @FXML
    private TableView<Runda> tblRunde;
    @FXML
    private TableColumn<Runda, String> colJucator;
    @FXML
    private TableColumn<Runda, String> colData;
    @FXML
    private TableColumn<Runda, String> colScor;
    @FXML
    private TableColumn<Runda, String> colIndiciu;

    ObservableList<Runda> model = FXCollections.observableArrayList();

    @Override
    public void newRunda(Runda runda) {

//        Platform.runLater(() -> {
//
//        });
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void setServer(IServices server) throws ServiceException {
        this.server = server;
        startGame();
        initModel();
        initialize();
    }

    private void initialize() {
        colJucator.setCellValueFactory(new PropertyValueFactory<>("alias"));
        colData.setCellValueFactory(new PropertyValueFactory<>("data"));
        colScor.setCellValueFactory(new PropertyValueFactory<>("nr_incercari"));
        colIndiciu.setCellValueFactory(new PropertyValueFactory<>("indiciu"));

        tblRunde.setItems(model);
    }

    private void initModel() throws ServiceException {
        lblDistanta.setEditable(false);
        lblNrIncercari.setEditable(false);
        lblIndiciu.setEditable(false);
        gameOver = false;

        model.setAll(server.getAllRunde());
    }

    public void logout() {
        try {
            server.logout(jucator, this);
        } catch (ServiceException e) {
            System.out.println("Logout error " + e);
        }
    }

    public void startGame() {
        try {
            runda = server.startGame(jucator);
        } catch (ServiceException e) {
            System.out.println("Start game error " + e);
        }
    }

    private void gameover() {

//        try {
//            server.addRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
//        } catch (ServiceException e) {
//            System.out.println("Add runda error " + e);
//            MessageAlert.showErrorMessage(null, e.getMessage());
//        }

        gameOver = true;
        lbl11.setText("X");
        lbl12.setText("X");
        lbl13.setText("X");
        lbl14.setText("X");
        lbl21.setText("X");
        lbl22.setText("X");
        lbl23.setText("X");
        lbl24.setText("X");
        lbl31.setText("X");
        lbl32.setText("X");
        lbl33.setText("X");
        lbl34.setText("X");
        lbl41.setText("X");
        lbl42.setText("X");
        lbl43.setText("X");
        lbl44.setText("X");

        lblDistanta.setText("");
        if (runda.getScor() == 10) {
            lblNrIncercari.setText("10");
            lblIndiciu.setText("");
        } else {
            lblIndiciu.setText(runda.getIndiciu());
        }

        try {
            server.addRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } catch (ServiceException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }

    }

    public void handle11(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 1 && runda.getColoana() == 1 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
            gameover();
        } else {
            lbl11.setText("X");
            lbl11.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(1, 1).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle12(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 1 && runda.getColoana() == 2 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl12.setText("X");
            lbl12.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(1, 2).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle13(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 1 && runda.getColoana() == 3 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl13.setText("X");
            lbl13.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(1, 3).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle14(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 1 && runda.getColoana() == 4 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl14.setText("X");
            lbl14.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(1, 4).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle21(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 2 && runda.getColoana() == 1 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl21.setText("X");
            lbl21.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(2, 1).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle31(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 3 && runda.getColoana() == 1 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl31.setText("X");
            lbl31.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(3, 1).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle22(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 2 && runda.getColoana() == 2 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl22.setText("X");
            lbl22.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(2, 2).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle32(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 3 && runda.getColoana() == 2 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl32.setText("X");
            lbl32.setStyle("-fx-text-fill: red");
            runda.setScor(runda.getScor() + 1);
            lblDistanta.setText(distance(3, 2).toString());
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle23(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 2 && runda.getColoana() == 3 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl23.setText("X");
            lbl23.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(2, 3).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle24(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 2 && runda.getColoana() == 4 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl24.setText("X");
            lbl24.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(2, 4).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle33(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
            return;
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 3 && runda.getColoana() == 3 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl33.setText("X");
            lbl33.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(3, 3).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle34(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 3 && runda.getColoana() == 4 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl34.setText("X");
            lbl34.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(3, 4).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle41(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 4 && runda.getColoana() == 1 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl41.setText("X");
            lbl41.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(4, 1).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle42(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 4 && runda.getColoana() == 2 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl42.setText("X");
            lbl42.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(4, 2).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle43(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 4 && runda.getColoana() == 3 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl43.setText("X");
            lbl43.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(4, 3).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    public void handle44(MouseEvent mouseEvent) {
        if (gameOver) {
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Game over", "Game over");
        }
        if (runda.getScor() == 10) {
            gameover();
        }
        if (runda.getLinie() == 4 && runda.getColoana() == 4 && !gameOver && runda.getScor() < 10) {
            newRunda(new Runda(jucator, runda.getData(), runda.getScor(), runda.getIndiciu()));
        } else {
            lbl44.setText("X");
            lbl44.setStyle("-fx-text-fill: red");
            lblDistanta.setText(distance(4, 4).toString());
            runda.setScor(runda.getScor() + 1);
            lblNrIncercari.setText(runda.getScor().toString());
        }
    }

    private Integer distance(int col, int row) {
        return Math.abs((runda.getColoana() - col) * (runda.getColoana() - col) + (runda.getLinie() - row) * (runda.getLinie() - row));
    }

    public void handleLogout(ActionEvent actionEvent) throws ServiceException {
        server.logout(jucator, this);
    }
}
