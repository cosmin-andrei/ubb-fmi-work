module com.example.sem7gui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires java.sql;

    opens com.example.sem7gui to javafx.fxml;
    exports com.example.sem7gui;


}