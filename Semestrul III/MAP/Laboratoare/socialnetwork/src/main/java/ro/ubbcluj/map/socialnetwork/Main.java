package ro.ubbcluj.map.socialnetwork;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.domain.validators.CerereValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.MessageValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.PrietenieValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.socialnetwork.repository.*;
import ro.ubbcluj.map.socialnetwork.service.CerereService;
import ro.ubbcluj.map.socialnetwork.service.MessageService;
import ro.ubbcluj.map.socialnetwork.service.PrietenieService;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        final String url = "jdbc:postgresql://localhost:5432/socialnetwork";
        final String username = "postgres";
        final String password = "2003";
        Repository<Long, Utilizator> repoUtilizator = new UserDBRepository(new UtilizatorValidator(), url, username, password);
        UtilizatorService serv = new UtilizatorService(repoUtilizator);

        CerereValidator cerereValidator = new CerereValidator();
        PrietenieValidator prietenieValidator = new PrietenieValidator();
        CerereDBRepository cerereDBRepository = new CerereDBRepository(cerereValidator, url, username, password);
        PrietenieDBRepository prietenieDBRepository = new PrietenieDBRepository(prietenieValidator, url, username, password);
        UtilizatorValidator utilizatorValidator = new UtilizatorValidator();
        UserDBRepository userDBRepository = new UserDBRepository(utilizatorValidator, url, username, password);
        CerereService cerereService = new CerereService(prietenieDBRepository, userDBRepository, cerereDBRepository);
        PrietenieService prietenieService = new PrietenieService(repoUtilizator, prietenieDBRepository);
        MessageDBRepository messageDBRepository = new MessageDBRepository(new MessageValidator(), url, username, password);
        MessageService messageService = new MessageService(messageDBRepository, prietenieDBRepository);


        FXMLLoader usersLoader = new FXMLLoader();
        usersLoader.setLocation(getClass().getResource("user-view.fxml"));

        Scene scene = new Scene(usersLoader.load());

        // Permiterea redimensionării ferestrei de către utilizator
        primaryStage.setResizable(true);

        primaryStage.setTitle("Retea de socializare");
        primaryStage.setScene(scene);

        UserController userController = usersLoader.getController();
        userController.setService(serv, cerereService, prietenieService, messageService);

        primaryStage.show();

    }

}
