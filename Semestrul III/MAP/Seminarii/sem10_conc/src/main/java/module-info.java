module com.example.sem10_conc {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;

    opens com.example.sem10_conc to javafx.fxml;
    exports com.example.sem10_conc;
}