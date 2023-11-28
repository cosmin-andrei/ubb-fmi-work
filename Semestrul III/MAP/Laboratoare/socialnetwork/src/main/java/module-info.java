module ro.ubbcluj.map.socialnetwork {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires java.sql;

    opens ro.ubbcluj.map.socialnetwork to javafx.fxml;
    opens ro.ubbcluj.map.socialnetwork.domain;
    exports ro.ubbcluj.map.socialnetwork;
}