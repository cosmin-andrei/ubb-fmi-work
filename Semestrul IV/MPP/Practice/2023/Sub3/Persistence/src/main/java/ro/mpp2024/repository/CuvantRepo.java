package ro.mpp2024.repository;

import ro.mpp2024.model.Cuvant;
import ro.mpp2024.repository.interfaces.CuvantRepoInterface;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class CuvantRepo implements CuvantRepoInterface {

    private JdbcUtils dbUtils;

    public CuvantRepo(Properties props) {
        this.dbUtils = new JdbcUtils(props);
    }

    @Override
    public List<Cuvant> generateWords(int n) {
        List<Cuvant> cuvinte = new ArrayList<>();
        Connection con = dbUtils.getConnection();
        String query = "SELECT * FROM cuvinte ORDER BY RANDOM() LIMIT ?";
        try (PreparedStatement preStmt = con.prepareStatement(query)) {
            preStmt.setInt(1, n);
            try (ResultSet rs = preStmt.executeQuery()) {
                while (rs.next()) {
                    Cuvant cuvant = new Cuvant();
                    cuvant.setId(rs.getString("id"));
                    cuvinte.add(cuvant);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return cuvinte;
    }


    @Override
    public Optional<Cuvant> findOne(String s) {
        return Optional.empty();
    }

    @Override
    public Iterable<Cuvant> findAll() {
        return null;
    }

    @Override
    public Optional<Cuvant> save(Cuvant entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Cuvant> delete(String s) {
        return Optional.empty();
    }

    @Override
    public Optional<Cuvant> update(Cuvant entity) {
        return Optional.empty();
    }
}
