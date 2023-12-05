package ro.ubbcluj.map.socialnetwork.repository;

import ro.ubbcluj.map.socialnetwork.domain.CererePrietenie;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.validators.CerereValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.ValidationException;

import java.sql.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class CerereDBRepository implements Repository<Tuple<Long, Long>, CererePrietenie> {

    private final CerereValidator validator;
    private final String url;
    private final String username;
    private final String password;

    public CerereDBRepository(CerereValidator validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public Optional<CererePrietenie> findOne(Tuple<Long, Long> longLongTuple) throws SQLException {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"requests\" WHERE id1 = ? AND id2 = ?;")) {
            statement.setLong(1, longLongTuple.getLeft());
            statement.setLong(2, longLongTuple.getRight());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    long id1 = resultSet.getLong("id1");
                    long id2 = resultSet.getLong("id2");
                    String status = resultSet.getString("status");
                    Timestamp date = resultSet.getTimestamp("date");

                    CererePrietenie request = new CererePrietenie();
                    request.setId(new Tuple<> (id1, id2));
                    request.setStatus(status);
                    request.setDate(date.toLocalDateTime());

                    return Optional.of(request);
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

        }

        return Optional.empty();
    }



    @Override
    public Iterable<CererePrietenie> findAll() {
        Set<CererePrietenie> requests = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"requests\";");
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                String status = resultSet.getString("status");
                Timestamp date = resultSet.getTimestamp("date");

                CererePrietenie cererePrietenie = new CererePrietenie();
                cererePrietenie.setId(new Tuple<>(id1, id2));
                cererePrietenie.setStatus(status);
                cererePrietenie.setDate(date.toLocalDateTime());

                requests.add(cererePrietenie);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return requests;
    }

    @Override
    public Optional<CererePrietenie> save(CererePrietenie entity) throws SQLException {

        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");

        if (findOne(entity.getId()).isPresent()) {
            String status = entity.getStatus();
            if (Objects.equals(status, "PENDING"))
                throw new ValidationException("Cererea exista deja");
        }

        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("insert into \"requests\"(id1,id2,status,date) values (?,?,?,?)")) {

            statement.setLong(1, entity.getId().getLeft());
            statement.setLong(2, entity.getId().getRight());
            statement.setString(3, entity.getStatus());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getDate()));

            statement.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<CererePrietenie> delete(Tuple<Long, Long> longLongTuple) {
        Optional<CererePrietenie> cererePrietenie = null;
        try {
            cererePrietenie = findOne(longLongTuple);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        if (cererePrietenie.isPresent()) {
            try (Connection connection = DriverManager.getConnection(url, username, password);
                 PreparedStatement statement = connection.prepareStatement("DELETE FROM \"requests\" WHERE id1 = ? AND id2 = ?;")) {

                statement.setLong(1, longLongTuple.getLeft());
                statement.setLong(2, longLongTuple.getRight());

                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return cererePrietenie;

        } else {
            return Optional.empty();
        }
    }

    @Override
    public Optional<CererePrietenie> update(CererePrietenie entity) throws SQLException {
        if (entity == null) {
            throw new IllegalArgumentException("Eroare, cerere null");
        }

        if (findOne(entity.getId()).isEmpty()) {
            throw new ValidationException("Cererea nu exista");
        }

        validator.validate(entity);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(
                     "UPDATE \"requests\" SET status = ?, date = ? WHERE id1 = ? AND id2 = ?"
             )) {

            statement.setString(1, entity.getStatus());
            statement.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            statement.setLong(3, entity.getId().getLeft());
            statement.setLong(4, entity.getId().getRight());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.empty();
    }
}
