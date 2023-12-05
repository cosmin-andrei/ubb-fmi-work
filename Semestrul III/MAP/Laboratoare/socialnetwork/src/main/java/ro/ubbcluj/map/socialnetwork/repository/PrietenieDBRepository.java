package ro.ubbcluj.map.socialnetwork.repository;

import ro.ubbcluj.map.socialnetwork.domain.Prietenie;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.validators.PrietenieValidator;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class PrietenieDBRepository implements Repository<Tuple<Long, Long>, Prietenie> {

    private final PrietenieValidator validator;
    private final String url;
    private final String username;
    private final String password;

    public PrietenieDBRepository(PrietenieValidator validator, String url, String username, String password) {
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
                if (resultSet.next()) {
                    Long id1 = resultSet.getLong("id1");
                    Long id2 = resultSet.getLong("id2");
                    Timestamp date = resultSet.getTimestamp("data");

                    Prietenie prietenie = new Prietenie();
                    prietenie.setId(new Tuple<>(id1, id2));
                    prietenie.setDate(date.toLocalDateTime());

                    return Optional.of(prietenie);
                }
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
             ResultSet resultSet = statement.executeQuery()) {

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
        if (entity == null) {
            throw new IllegalArgumentException("entity must not be null");
        }

        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO friends (id1, id2, data) VALUES (?, ?, ?)")) {

            statement.setLong(1, entity.getId().getLeft());
            statement.setLong(2, entity.getId().getRight());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDate()));

            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> longLongTuple) {
        Optional<Prietenie> prietenie = findOne(longLongTuple);

        if (prietenie.isPresent()) {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("DELETE FROM \"friends\" WHERE id1 = ? AND id2 = ?;")) {

                statement.setLong(1, longLongTuple.getLeft());
                statement.setLong(2, longLongTuple.getRight());

                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return prietenie;
        } else {
            return Optional.empty();
        }
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        // No update logic for now
        return Optional.empty();
    }
}
