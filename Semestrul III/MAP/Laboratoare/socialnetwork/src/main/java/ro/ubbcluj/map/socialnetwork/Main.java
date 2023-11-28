package ro.ubbcluj.map.socialnetwork;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import ro.ubbcluj.map.socialnetwork.domain.Prietenie;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.Utilizator;
import ro.ubbcluj.map.socialnetwork.domain.validators.PrietenieValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.socialnetwork.repository.PrietenieDBRepo;
import ro.ubbcluj.map.socialnetwork.repository.Repository;
import ro.ubbcluj.map.socialnetwork.repository.UserDBRepository;
import ro.ubbcluj.map.socialnetwork.service.PrietenieService;
import ro.ubbcluj.map.socialnetwork.service.UtilizatorService;

public class Main extends Application {

    //Button button;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        final String url = "jdbc:postgresql://localhost:5432/socialnetwork";
        final String username = "postgres";
        final String password = "2003";
        Repository<Long, Utilizator> repoUtilizator = new UserDBRepository(new UtilizatorValidator(), url, username, password);
        Repository<Tuple<Long, Long>, Prietenie> repoPrietenie = new PrietenieDBRepo(new PrietenieValidator(), url, username, password);

        UtilizatorService serv = new UtilizatorService(repoUtilizator);
        PrietenieService prietenieService = new PrietenieService(repoUtilizator, repoPrietenie);

        FXMLLoader usersLoader = new FXMLLoader();
        usersLoader.setLocation(getClass().getResource("user-view.fxml"));

        Scene scene = new Scene(usersLoader.load(), 500, 400);
        primaryStage.setTitle("Retea de socializare");
        primaryStage.setScene(scene);

        UserController userController = usersLoader.getController();
        userController.setService(serv);

        primaryStage.show();

    }

}
