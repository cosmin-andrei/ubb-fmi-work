package ro.mpp2024.repository;

import ro.mpp2024.model.Cuvant;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class RundaRepo implements RundaRepoInterface {

    JdbcUtils jdbcUtils;

    public RundaRepo(Properties props) {
        jdbcUtils = new JdbcUtils(props);
    }

    @Override
    public Optional<Runda> findOne(Long aLong) {
        Connection con = jdbcUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("select * from Runde where id=?")) {
            preStmt.setLong(1, aLong);
            preStmt.executeQuery();
            try (ResultSet rs = preStmt.executeQuery()) {
                while (rs.next()) {
                    Runda runda = new Runda(new Jucator(rs.getString("jucator")), rs.getInt("scor"));
                    runda.setId(rs.getLong("id"));
                    return Optional.of(runda);
                }
            }
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Runda> findAll() {
        List<Runda> runde = new ArrayList<>();
        Connection con = jdbcUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("select * from Runde")) {
            try (ResultSet rs = preStmt.executeQuery()) {
                while (rs.next()) {
                    Runda runda = new Runda(new Jucator(rs.getString("jucator")), rs.getInt("scor"));
                    runda.setId(rs.getLong("id"));
                    runda.setDurata(rs.getLong("durata"));
                    runde.add(runda);
                }
            }
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }
        return runde;
    }

    @Override
    public Optional<Runda> save(Runda entity) {

        Connection con = jdbcUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("insert into Runde(id, jucator, scor, durata) values (?, ?, ?, ?)")) {
            preStmt.setLong(1, entity.getId());
            preStmt.setString(2, entity.getJucator().getId());
            preStmt.setInt(3, entity.getScor());
            preStmt.setLong(4, entity.getDurata());
            preStmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }

        return Optional.ofNullable(entity);

    }

    @Override
    public Optional<Runda> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Runda> update(Runda entity) {
        Connection con = jdbcUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("update Runde set jucator=?, scor=?, durata=? where id=?")) {
            preStmt.setString(1, entity.getJucator().getId());
            preStmt.setInt(2, entity.getScor());
            preStmt.setLong(3, entity.getDurata());
            preStmt.setLong(4, entity.getId());
            preStmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error DB " + e);
        }
        return Optional.ofNullable(entity);
    }
}
