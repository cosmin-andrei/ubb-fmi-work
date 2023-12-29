module com.projects.socialnetwork {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.projects.socialnetwork to javafx.fxml;
    exports com.projects.socialnetwork;
    exports com.projects.socialnetwork.ui;
    opens com.projects.socialnetwork.ui to javafx.fxml;
    exports com.projects.socialnetwork.controllers;
    opens com.projects.socialnetwork.controllers to javafx.fxml;
    exports com.projects.socialnetwork.models;
    opens com.projects.socialnetwork.models to javafx.base;
}