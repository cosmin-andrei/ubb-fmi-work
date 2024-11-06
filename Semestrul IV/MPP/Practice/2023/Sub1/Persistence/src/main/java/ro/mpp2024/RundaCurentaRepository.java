package ro.mpp2024;

import ro.mpp2024.IRepositories.IRundaCurentaRepo;
import ro.mpp2024.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Optional;
import java.util.Properties;

public class RundaCurentaRepository implements IRundaCurentaRepo {

    private JdbcUtils dbUtils;

    public RundaCurentaRepository(Properties props) {
        this.dbUtils = new JdbcUtils(props);
    }

    @Override
    public Optional<RundaCurenta> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<RundaCurenta> findAll() {
        return null;
    }

    @Override
    public Optional<RundaCurenta> save(RundaCurenta entity) {
        Connection con = dbUtils.getConnection();
        try (PreparedStatement preStmt = con.prepareStatement("insert into runda_curenta values (?, ?, ?, ?,?,?,?)")) {
            preStmt.setLong(1, entity.getId());
            preStmt.setString(2, entity.getJucator().getId());
            preStmt.setInt(3, entity.getScor());
            preStmt.setString(4, entity.getIndiciu());
            preStmt.setInt(5, entity.getLinie());
            preStmt.setInt(6, entity.getColoana());
            preStmt.setTimestamp(7, entity.getData());
            preStmt.executeUpdate();
            return Optional.of(entity);
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<RundaCurenta> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<RundaCurenta> update(RundaCurenta entity) {
        return Optional.empty();
    }

    @Override
    public void deleteByJucator(Jucator jucator) {
        Connection con = dbUtils.getConnection();
        try (PreparedStatement preStmt = con.prepareStatement("delete from runda_curenta where alias=?")) {
            preStmt.setString(1, jucator.getId());
            preStmt.executeUpdate();
        } catch (Exception e) {
            System.out.println("Error DB " + e);
        }
    }
}
