package ro.mpp2024;

import ro.mpp2024.IRepositories.IJucatorRepo;
import ro.mpp2024.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;
import java.util.Properties;

public class JucatorRepository implements IJucatorRepo {

    private JdbcUtils dbUtils;

    public JucatorRepository(Properties props) {
        this.dbUtils = new JdbcUtils(props);
    }

    @Override
    public Optional<Jucator> findOne(String s) {
        Connection con = dbUtils.getConnection();
        try (PreparedStatement preStmt = con.prepareStatement("select * from jucator where alias=?")) {
            preStmt.setString(1, s);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    Jucator jucator = getJucator(result);
                    return Optional.of(jucator);
                }
            }
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }

        return Optional.empty();
    }

    private Jucator getJucator(ResultSet result) throws SQLException {
        String alias = result.getString("alias");
        return new Jucator(alias);
    }

    @Override
    public Iterable<Jucator> findAll() {
        return null;
    }

    @Override
    public Optional<Jucator> save(Jucator entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Jucator> delete(String s) {
        return Optional.empty();
    }

    @Override
    public Optional<Jucator> update(Jucator entity) {
        return Optional.empty();
    }
}
