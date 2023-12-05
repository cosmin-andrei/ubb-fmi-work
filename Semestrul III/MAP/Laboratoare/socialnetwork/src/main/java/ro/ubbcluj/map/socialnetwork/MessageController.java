package ro.ubbcluj.map.socialnetwork;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.service.MessageService;

public class MessageController {
    private MessageService messageService;
    private final ObservableList<Utilizator> model = FXCollections.observableArrayList();
    private Long id;
    private Stage dialogStage;
    public void setService(MessageService messageService, Stage dialogStage, Long id) {
        this.messageService=messageService;
        this.id = id;
        this.dialogStage = dialogStage;
    }
}
