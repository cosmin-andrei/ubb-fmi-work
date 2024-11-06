package ro.mpp2024.controller;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.util.Duration;
import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Cuvant;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.time.Instant;
import java.util.Comparator;
import java.util.Objects;

import static javafx.scene.control.Alert.AlertType.INFORMATION;

public class MainController implements IObserver {

    ObservableList<Runda> model = FXCollections.observableArrayList();
    private IServices server;
    private Jucator jucator;
    private Integer count = 0;
    private Configuratie configuratie;
    private String cuv1, cuv2;
    private int pozcuv1;
    private boolean game = false;
    private Runda runda;
    private Long k;
    private int perechi;
    private Instant startTime;
    private Instant endTime;


    @FXML
    private TableView<Runda> tblClasament;
    @FXML
    private TableColumn<Runda, String> colJucator;
    @FXML
    private TableColumn<Runda, Integer> colScor;
    @FXML
    private TableColumn<Runda, Long> colDurata;

    @FXML
    private Label poz1;
    @FXML
    private Label poz2;
    @FXML
    private Label poz3;
    @FXML
    private Label poz4;
    @FXML
    private Label poz5;
    @FXML
    private Label poz6;
    @FXML
    private Label poz7;
    @FXML
    private Label poz8;
    @FXML
    private Label poz9;
    @FXML
    private Label poz10;

    public MainController() {
    }

    public void setServer(IServices service) throws ServiceException {
        this.server = service;
        initmodel();
        initialize();
    }

    private void initialize() {
        colJucator.setCellValueFactory(new PropertyValueFactory<>("jucator"));
        colScor.setCellValueFactory(new PropertyValueFactory<>("scor"));
        colDurata.setCellValueFactory(new PropertyValueFactory<>("durata"));
        tblClasament.setItems(model);
    }

    private void initmodel() throws ServiceException {
        this.configuratie = server.startGame(jucator);
        this.startTime = Instant.now();
        this.runda = server.getRunda(configuratie.getRunda().getId());
        this.k = 0L;
        this.perechi = 0;
        model.setAll(server.getClasament());
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

    private void verify(int poz) {

        if (k == 10) {
            gameOver();
            return;
        }

        if (perechi == 5) {
            gameOver();
            return;
        }

        Cuvant cuv = findCuv(poz);
        if (count == 2) {
            assert cuv != null;
            cuv2 = cuv.getId();
            k++;
            if (Objects.equals(cuv1, cuv2)) {
                perechi++;
                cuv1 = cuv2 = "";
                count = 0;
                runda.setScor(runda.getScor()+3);
            } else {
                Timeline timeline = new Timeline(new KeyFrame(
                        Duration.seconds(1),
                        ae -> resetPozConfig(poz)
                ));
                timeline.play();
                cuv1 = cuv2 = "";
                count = 0;
                runda.setScor(runda.getScor()-2);
            }
        } else {
            assert cuv != null;
            cuv1 = cuv.getId();
            pozcuv1 = poz;
        }
    }

    private void resetPozConfig(int poz) {
        removePozConfig(pozcuv1);
        removePozConfig(poz);
    }

    private void removePozConfig(int poz) {
        if (poz == 1) {
            poz1.setText("1");
        }
        if (poz == 2) {
            poz2.setText("2");
        }
        if (poz == 3) {
            poz3.setText("3");
        }
        if (poz == 4) {
            poz4.setText("4");
        }
        if (poz == 5) {
            poz5.setText("5");
        }
        if (poz == 6) {
            poz6.setText("6");
        }
        if (poz == 7) {
            poz7.setText("7");
        }
        if (poz == 8) {
            poz8.setText("8");
        }
        if (poz == 9) {
            poz9.setText("9");
        }
        if (poz == 10) {
            poz10.setText("10");
        }
    }

    private void showPozConfig(int poz) {
        if (poz == 1) {
            poz1.setText(configuratie.getPoz1().getId());
        }
        if (poz == 2) {
            poz2.setText(configuratie.getPoz2().getId());
        }
        if (poz == 3) {
            poz3.setText(configuratie.getPoz3().getId());
        }
        if (poz == 4) {
            poz4.setText(configuratie.getPoz4().getId());
        }
        if (poz == 5) {
            poz5.setText(configuratie.getPoz5().getId());
        }
        if (poz == 6) {
            poz6.setText(configuratie.getPoz6().getId());
        }
        if (poz == 7) {
            poz7.setText(configuratie.getPoz7().getId());
        }
        if (poz == 8) {
            poz8.setText(configuratie.getPoz8().getId());
        }
        if (poz == 9) {
            poz9.setText(configuratie.getPoz9().getId());
        }
        if (poz == 10) {
            poz10.setText(configuratie.getPoz10().getId());
        }
    }

    private Cuvant findCuv(int poz) {
        if (poz == 1) {
            return configuratie.getPoz1();
        }
        if (poz == 2) {
            return configuratie.getPoz2();
        }
        if (poz == 3) {
            return configuratie.getPoz3();
        }
        if (poz == 4) {
            return configuratie.getPoz4();
        }
        if (poz == 5) {
            return configuratie.getPoz5();
        }
        if (poz == 6) {
            return configuratie.getPoz6();
        }
        if (poz == 7) {
            return configuratie.getPoz7();
        }
        if (poz == 8) {
            return configuratie.getPoz8();
        }
        if (poz == 9) {
            return configuratie.getPoz9();
        }
        if (poz == 10) {
            return configuratie.getPoz10();
        }
        return null;
    }

    private void gameOver() {
        this.endTime = Instant.now();
        long duration = java.time.Duration.between(startTime, endTime).getSeconds();
        runda.setDurata(duration);
        game = true;
        try {
            server.updateRunda(runda);
        } catch (ServiceException e) {
            System.out.println("Update runda error " + e);
        }

        if (k == 10) {
            MessageAlert.showErrorMessage(null, "Game over. Ai pierdut");
        } else {
            MessageAlert.showMessage(null, INFORMATION, "Felicitari", "Ai castigat!");
        }

        showConfig();

    }

    private void showConfig() {
        poz1.setText(configuratie.getPoz1().getId());
        poz2.setText(configuratie.getPoz2().getId());
        poz3.setText(configuratie.getPoz3().getId());
        poz4.setText(configuratie.getPoz4().getId());
        poz5.setText(configuratie.getPoz5().getId());
        poz6.setText(configuratie.getPoz6().getId());
        poz7.setText(configuratie.getPoz7().getId());
        poz8.setText(configuratie.getPoz8().getId());
        poz9.setText(configuratie.getPoz9().getId());
        poz10.setText(configuratie.getPoz10().getId());
    }

    public void handle1(MouseEvent mouseEvent) {
        count++;
        showPozConfig(1);
        verify(1);
    }

    public void handle2(MouseEvent mouseEvent) {
        count++;
        showPozConfig(2);
        verify(2);
    }

    public void handle3(MouseEvent mouseEvent) {
        count++;
        showPozConfig(3);
        verify(3);
    }

    public void handle4(MouseEvent mouseEvent) {
        count++;
        showPozConfig(4);
        verify(4);
    }

    public void handle5(MouseEvent mouseEvent) {
        count++;
        showPozConfig(5);
        verify(5);
    }

    public void handle6(MouseEvent mouseEvent) {
        count++;
        showPozConfig(6);
        verify(6);
    }

    public void handle7(MouseEvent mouseEvent) {
        count++;
        showPozConfig(7);
        verify(7);
    }

    public void handle8(MouseEvent mouseEvent) {
        count++;
        showPozConfig(8);
        verify(8);
    }

    public void handle9(MouseEvent mouseEvent) {
        count++;
        showPozConfig(9);
        verify(9);
    }

    public void handle10(MouseEvent mouseEvent) {
        count++;
        showPozConfig(10);
        verify(10);
    }

    @Override
    public void newRunda(Runda runda) {
        Platform.runLater(() -> {
            System.out.println("Mesaj runLater new "+ runda);
            model.add(runda);
            model.sort(Comparator.comparing(Runda::getScor));

            tblClasament.setItems(model);
            tblClasament.refresh();
        });
    }
}
