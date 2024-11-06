package ro.mpp2024.controller;

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
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.sql.Time;
import java.time.Instant;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import static javafx.scene.control.Alert.AlertType.INFORMATION;

public class MainController implements IObserver {

    @FXML
    public Label poz1;
    @FXML
    public Label poz2;
    @FXML
    public Label poz3;
    @FXML
    public Label poz4;
    @FXML
    public Label poz5;
    @FXML
    public Label poz6;
    @FXML
    public Label poz7;
    @FXML
    public Label poz8;
    @FXML
    public Label poz9;
    @FXML
    public TableColumn colPlayer;
    @FXML
    public TableView tblClasament;
    @FXML
    public TableColumn colDurata;
    @FXML
    public TableColumn colScor;
    ObservableList<Runda> model = FXCollections.observableArrayList();
    private IServices server;
    private Jucator jucator;

    private boolean gameOver = false;
    private boolean gameWin = false;
    private Map<Long, String> board;
    private Integer nrMutari = 0;
    private Integer durata;
    private Instant startTime;


    public void setServer(IServices service) throws ServiceException {
        this.server = service;
        initmodel();
        initialize();
    }

    private void initialize() {
        colPlayer.setCellValueFactory(new PropertyValueFactory<>("player"));
        colScor.setCellValueFactory(new PropertyValueFactory<>("scor"));
        colDurata.setCellValueFactory(new PropertyValueFactory<>("durata"));
        tblClasament.setItems(model);
    }

    private void initmodel() throws ServiceException {
        board = new HashMap<>();
        for (int i = 1; i <= 9; i++) {
            board.put((long) i, "");
        }
        this.durata = 0;
        this.startTime = Instant.now();
        model.setAll(server.getAllRunda());
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

    public void handlePoz1(MouseEvent mouseEvent) throws ServiceException {
        if (!gameOver) {
            if (verify()) return;
            if (poz1.getText().isEmpty()) {
                poz1.setText("X");
                board.put(1L, "X");
                if (verifyGame())
                    return;
                Long poz = server.chooseMove(jucator, board);
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    private boolean verifyGame() {
        if (verifyGameWin()) {
            if (gameWin) {
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
                return true;
            } else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
        return false;
    }

    public void handlePoz2(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz2.getText().isEmpty()) {
                poz2.setText("X");
                board.replace(2L, "X");
                Long poz = null;
                if (verifyGame())
                    return;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz3(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz3.getText().isEmpty()) {
                poz3.setText("X");
                board.replace(3L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    private boolean verify() {
        if (nrMutari == 9) {
            gameOver = true;
            return true;
        }
        return false;
    }

    public void handlePoz4(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz4.getText().isEmpty()) {
                poz4.setText("X");
                board.replace(4L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz5(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz5.getText().isEmpty()) {
                poz5.setText("X");
                board.replace(5L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz6(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz6.getText().isEmpty()) {
                poz6.setText("X");
                board.replace(6L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz7(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz7.getText().isEmpty()) {
                poz7.setText("X");
                board.replace(7L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz8(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz8.getText().isEmpty()) {
                poz8.setText("X");
                board.replace(8L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    public void handlePoz9(MouseEvent mouseEvent) {
        if (!gameOver) {
            if (verify()) return;
            if (poz9.getText().isEmpty()) {
                poz9.setText("X");
                board.replace(9L, "X");
                if (verifyGame())
                    return;
                Long poz = null;
                try {
                    poz = server.chooseMove(jucator, board);
                } catch (ServiceException e) {
                    throw new RuntimeException(e);
                }
                modifyBoard(poz);
                nrMutari += 2;

            } else {
                MessageAlert.showErrorMessage(null, "Pozitie ocupata");
            }

        } else {
            if (gameWin)
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat deja!");
            else {
                MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
            }
        }
    }

    private void modifyBoard(Long poz) {
        if (poz == 1) {
            poz1.setText("0");
            board.replace(1L, "0");
        }
        if (poz == 2) {
            poz2.setText("0");
            board.replace(2L, "0");
        }
        if (poz == 3) {
            poz3.setText("0");
            board.replace(3L, "0");
        }
        if (poz == 4) {
            poz4.setText("0");
            board.replace(4L, "0");
        }
        if (poz == 5) {
            poz5.setText("0");
            board.replace(5L, "0");
        }
        if (poz == 6) {
            poz6.setText("0");
            board.replace(6L, "0");
        }
        if (poz == 7) {
            poz7.setText("0");
            board.replace(7L, "0");
        }
        if (poz == 8) {
            poz8.setText("0");
            board.replace(8L, "0");
        }
        if (poz == 9) {
            poz9.setText("0");
            board.replace(9L, "0");
        }
    }

    private boolean verifyGameWin() {
        try {
            if (Objects.equals(server.verifyGameWin(board), "X")) {
                System.out.println(server.verifyGameWin(board));
                gameOver = true;
                gameWin = true;
                this.durata = (int) java.time.Duration.between(startTime, Instant.now()).getSeconds();
                server.addRunda(new Runda(jucator.getId(), 10, durata));
                MessageAlert.showMessage(null, INFORMATION, "Bravo", "Ai castigat!");
                return true;
            } else {
                if (Objects.equals(server.verifyGameWin(board), "0")) {
                    gameOver = true;
                    gameWin = false;
                    MessageAlert.showMessage(null, INFORMATION, "Game Over", "Jocul s-a terminat!");
                    return true;
                }
            }
        } catch (ServiceException e) {
            throw new RuntimeException(e);
        }
        return false;
    }


    @Override
    public void addRunda(Runda runda) {
        Platform.runLater(() -> {
            model.add(runda);
            model.sort(Comparator.comparing(Runda::getScor));

            tblClasament.setItems(model);
            tblClasament.refresh();
        });
    }
}
