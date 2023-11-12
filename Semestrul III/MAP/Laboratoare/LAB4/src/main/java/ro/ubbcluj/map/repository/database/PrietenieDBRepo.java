package ro.ubbcluj.map.repository.database;

import ro.ubbcluj.map.domain.Prietenie;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.validators.PrietenieValidator;
import ro.ubbcluj.map.repository.Repository;

import java.sql.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class PrietenieDBRepo implements Repository<Tuple<Long, Long>, Prietenie> {

    private final PrietenieValidator validator;
    private final String url;
    private final String username;
    private final String password;

    public PrietenieDBRepo(PrietenieValidator validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Prietenie> findOne(Tuple<Long, Long> longLongTuple) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"friends\" WHERE id1 = ? AND id2 = ?;")) {
            statement.setLong(1, longLongTuple.getLeft());
            statement.setLong(2, longLongTuple.getRight());
            try (ResultSet resultSet = statement.executeQuery()) {

                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                Timestamp date = resultSet.getTimestamp("data");

                Prietenie prietenie = new Prietenie();
                prietenie.setId(new Tuple<>(id1, id2));
                prietenie.setDate(date.toLocalDateTime());


            } catch (SQLException e) {
                throw new RuntimeException(e);
            }


        } catch (SQLException e) {
            throw new RuntimeException(e);

        }
        return Optional.empty();
    }

    @Override
    public Iterable<Prietenie> findAll() {
        Set<Prietenie> prietenii = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"friends\";");
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                Timestamp date = resultSet.getTimestamp("data");

                Prietenie prietenie = new Prietenie();
                prietenie.setId(new Tuple<>(id1, id2));
                prietenie.setDate(date.toLocalDateTime());

                prietenii.add(prietenie);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return prietenii;
    }

    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");

        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("insert into friends(id1,id2,data) values (?,?,?)")) {

            statement.setInt(1, entity.getId().getLeft().intValue());
            statement.setInt(2, entity.getId().getRight().intValue());
            statement.setDate(3, Date.valueOf(entity.getDate().toLocalDate()));

            statement.executeUpdate();

        }catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }

    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> longLongTuple) {
        Optional<Prietenie> prietenie = findOne(longLongTuple);

        if(prietenie.isPresent()){
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("DELETE FROM \"friends\" WHERE id1 = ? AND id2 = ?;")) {

                statement.setLong(1, longLongTuple.getLeft());
                statement.setLong(2, longLongTuple.getRight());

                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return prietenie;
        }else {
            return Optional.empty();
        }
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        return Optional.empty();
    }
}

