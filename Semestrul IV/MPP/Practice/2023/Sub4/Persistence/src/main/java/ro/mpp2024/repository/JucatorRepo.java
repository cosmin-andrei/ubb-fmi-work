package ro.mpp2024.repository;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.repository.interfaces.JucatorRepoInterface;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class JucatorRepo implements JucatorRepoInterface {

    private JdbcUtils dbUtils;

    private static final Logger logger= LogManager.getLogger();

    public JucatorRepo(Properties props) {
        logger.info("Initializing JucatorRepo with properties: {}", props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Optional<Jucator> findOne(String s) {
        Connection con = dbUtils.getConnection();
        logger.info("Finding jucator with alias: {}", s);
        try (PreparedStatement preStmt = con.prepareStatement("select * from Jucator where alias=?")) {
            preStmt.setString(1, s);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    Jucator jucator = getJucator(result);
                    return Optional.of(jucator);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.out.println("Error DB " + e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Jucator> findAll() {
        logger.info("Finding all jucatori");
        Connection con = dbUtils.getConnection();
        List<Jucator> jucatori = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Jucator")) {
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    Jucator jucator = getJucator(result);
                    jucatori.add(jucator);
                }
            }
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }
        return jucatori;
    }

    private static Jucator getJucator(ResultSet result) throws SQLException {
        String username = result.getString("alias");
        Jucator jucator = new Jucator(username);
        return jucator;
    }

    @Override
    public Optional<Jucator> save(Jucator entity) {
        logger.info("Saving jucator: {}", entity);
        return Optional.empty();
    }

    @Override
    public Optional<Jucator> delete(String s) {
        logger.info("Deleting jucator with alias: {}", s);
        return Optional.empty();
    }

    @Override
    public Optional<Jucator> update(Jucator entity) {
        logger.info("Updating jucator: {}", entity);
        return Optional.empty();
    }

}
