package ro.ubbcluj.map.socialnetwork;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.controller.MessageAlert;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.observer.Observer;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

public class EditUserController {
    private UtilizatorService utilizatorService;
    private Stage stage;
    private Utilizator user;
    @FXML
    private TextField textFieldID;
    @FXML
    private TextField textFieldNume;
    @FXML
    private TextField textFieldPrenume;
    @FXML
    private Button buttonSave;
    @FXML
    private Button buttonCancel;

    public void setUtilizatorService(UtilizatorService utilizatorService, Stage stage, Utilizator user) {
        this.utilizatorService = utilizatorService;
        this.stage = stage;
        this.user = user;

        if(user != null){
            textFieldID.setText(user.getId().toString());
            textFieldNume.setText(user.getFirstName());
            textFieldPrenume.setText(user.getLastName());

            //campul de id devine ineditabil
            textFieldID.setEditable(false);
        }
    }

    public void handleSave(ActionEvent actionEvent) {
        String id = textFieldID.getText();
        String firstName = textFieldNume.getText();
        String lastName = textFieldPrenume.getText();
        if(user == null)
            saveUser(id, firstName, lastName);
        else
            updateUser(id, firstName, lastName);

    }

    private void saveUser(String id,String firstName,String lastName) {
        try{
            Utilizator utilizator = new Utilizator(firstName, lastName);
            utilizator.setId(Long.valueOf(id));
            utilizatorService.adaugaUtilizator(utilizator);
            MessageAlert.showMessage(stage, Alert.AlertType.INFORMATION,"Adaugare utilizator","Utilizator adaugat cu succes!");
            stage.close();
        }catch(Exception e){
            MessageAlert.showErrorMessage(stage,e.getMessage());
        }
    }

    private void updateUser(String id,String firstName,String lastName) {
        try{
            Utilizator utilizator = new Utilizator(firstName, lastName);
            utilizator.setId(Long.valueOf(id));
            utilizatorService.updateUtilizator(utilizator);
            MessageAlert.showMessage(stage, Alert.AlertType.INFORMATION,"Update","Utilizator actualizat cu succes!");
            stage.close();
        }catch(Exception e){
            MessageAlert.showErrorMessage(stage,e.getMessage());
        }
    }

    public void handleCancel(ActionEvent actionEvent) {
        stage.close();
    }
}
