package ro.mpp2024;

import ro.mpp2024.IRepositories.IRundaRepo;
import ro.mpp2024.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class RundaRepository implements IRundaRepo {

    private JdbcUtils dbUtils;

    public RundaRepository(Properties props) {
        this.dbUtils = new JdbcUtils(props);
    }

    @Override
    public Optional<Runda> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Runda> findAll() {
        Connection con = dbUtils.getConnection();
        List<Runda> all = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from runda")) {
            try (var result = preStmt.executeQuery()) {
                while (result.next()) {
                    Long id = result.getLong("id");
                    String jucator = result.getString("alias");
                    java.sql.Timestamp data = result.getTimestamp("data");
                    int nr_incercari = result.getInt("nr_incercari");
                    String indiciu = result.getString("indiciu");
                    Runda runda = new Runda(new Jucator(jucator), data, nr_incercari, indiciu);
                    runda.setId(id);
                    all.add(runda);
                }
            }
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return all;
    }

    @Override
    public Optional<Runda> save(Runda entity) {
        Connection con = dbUtils.getConnection();
        try (PreparedStatement preStmt = con.prepareStatement("insert into runda values (?, ?, ?, ?,?)")) {
            preStmt.setLong(1, entity.getId());
            preStmt.setString(2, entity.getJucator().getId());
            preStmt.setTimestamp(3, entity.getData());
            preStmt.setInt(4, entity.getNr_incercari());
            preStmt.setString(5, entity.getIndiciu());
            preStmt.executeUpdate();
            return Optional.of(entity);
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Runda> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Runda> update(Runda entity) {
        return Optional.empty();
    }
}
