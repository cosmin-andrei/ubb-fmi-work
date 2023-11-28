package ro.ubbcluj.map.socialnetwork.observer;

import java.sql.SQLException;

public interface Observer {
    public void update() throws SQLException;
}
