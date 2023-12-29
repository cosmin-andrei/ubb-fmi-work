package com.projects.socialnetwork.repositories;

import com.projects.socialnetwork.models.User;
import com.projects.socialnetwork.validators.UserValidator;
import com.projects.socialnetwork.validators.Validator;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.UUID;

public class UserDBRepository implements Repository<UUID, User> {

    protected String url;
    protected String username;
    protected String password;

    private Validator<User> validator;

    public UserDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
        validator = new UserValidator();
    }

    @Override
    public Optional<User> getById(UUID uuid) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from users where id = ?")) {
            statement.setObject(1, uuid, Types.OTHER);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");
                String username = resultSet.getString("username");
                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                User user = new User(firstName, lastName, username, email, password);
                user.setId(uuid);

                //get all friends of the user
                PreparedStatement statement1 = connection.prepareStatement("\n" +
                        "SELECT u1.id AS user1_id, u1.firstname AS user1_firstname, u1.lastname AS user1_lastname, u1.email AS user1_email, u1.username AS user1_username,u1.password as user1_password,\n" +
                        "       u2.id AS user2_id, u2.firstname AS user2_firstname, u2.lastname AS user2_lastname, u2.email AS user2_email, u2.username AS user2_username, u2.password as user2_password\n" +
                        "FROM friendships AS f\n" +
                        "         LEFT JOIN users AS u1 ON f.user1_id = u1.id\n" +
                        "         LEFT JOIN users AS u2 ON f.user2_id = u2.id\n" +
                        "where user1_id = ? or user2_id = ?" +
                        "order by friends_since asc");

                statement1.setObject(1, uuid, Types.OTHER);
                statement1.setObject(2, uuid, Types.OTHER);
                ResultSet resultSet1 = statement1.executeQuery();

                while (resultSet1.next()) {
                    String user1_id = resultSet1.getString("user1_id");
                    String user2_id = resultSet1.getString("user2_id");
                    if (user1_id != null && user2_id != null) {
                        UUID user1_id_uuid = UUID.fromString(user1_id);
                        UUID user2_id_uuid = UUID.fromString(user2_id);
                        if (user1_id_uuid.equals(uuid)) {
                            String user2_firstname = resultSet1.getString("user2_firstname");
                            String user2_lastname = resultSet1.getString("user2_lastname");
                            String user2_username = resultSet1.getString("user2_username");
                            String user2_email = resultSet1.getString("user2_email");
                            String user2_password = resultSet1.getString("user2_password");
                            User user2 = new User(user2_firstname, user2_lastname, user2_username, user2_email, user2_password);
                            user2.setId(user2_id_uuid);
                            user.addFriend(user2);
                        }

                        if (user2_id_uuid.equals(uuid)) {
                            String user1_firstname = resultSet1.getString("user1_firstname");
                            String user1_lastname = resultSet1.getString("user1_lastname");
                            String user1_username = resultSet1.getString("user1_username");
                            String user1_email = resultSet1.getString("user1_email");
                            String user1_password = resultSet1.getString("user1_password");
                            User user1 = new User(user1_firstname, user1_lastname, user1_username, user1_email, user1_password);
                            user1.setId(user1_id_uuid);
                            user.addFriend(user1);
                        }
                    }
                }
                return Optional.of(user);
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<User> getAll() {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from users");
             ResultSet resultSet = statement.executeQuery()
        ) {
            Set<User> users = new HashSet<>();
            while (resultSet.next()) {
                UUID id = UUID.fromString(resultSet.getString("id"));
                String firstName = resultSet.getString("firstname");
                String lastName = resultSet.getString("lastname");
                String username = resultSet.getString("username");

                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                User user = new User(firstName, lastName, username, email, password);
                user.setId(id);
                users.add(user);
                //get all friends of the user
                PreparedStatement statement1 = connection.prepareStatement("\n" +
                        "SELECT u1.id AS user1_id, u1.firstname AS user1_firstname, u1.lastname AS user1_lastname, u1.email AS user1_email, u1.username AS user1_username,u1.password as user1_password,\n" +
                        "       u2.id AS user2_id, u2.firstname AS user2_firstname, u2.lastname AS user2_lastname, u2.email AS user2_email, u2.username AS user2_username, u2.password as user2_password\n" +
                        "FROM friendships AS f\n" +
                        "         LEFT JOIN users AS u1 ON f.user1_id = u1.id\n" +
                        "         LEFT JOIN users AS u2 ON f.user2_id = u2.id\n" +
                        "where user1_id = ? or user2_id = ?");
                statement1.setObject(1, user.getId(), Types.OTHER);
                statement1.setObject(2, user.getId(), Types.OTHER);
                ResultSet resultSet1 = statement1.executeQuery();

                while (resultSet1.next()) {
                    String user1_id = resultSet1.getString("user1_id");
                    String user2_id = resultSet1.getString("user2_id");
                    if (user1_id != null && user2_id != null) {
                        UUID user1_id_uuid = UUID.fromString(user1_id);
                        UUID user2_id_uuid = UUID.fromString(user2_id);

                        if (user1_id_uuid.equals(user.getId())) {
                            String user2_firstname = resultSet1.getString("user2_firstname");
                            String user2_lastname = resultSet1.getString("user2_lastname");
                            String user2_username = resultSet1.getString("user2_username");
                            String user2_email = resultSet1.getString("user2_email");
                            String user2_password = resultSet1.getString("user2_password");

                            User user2 = new User(user2_firstname, user2_lastname, user2_username, user2_email, user2_password);
                            user2.setId(user2_id_uuid);
                            user.addFriend(user2);
                        }

                        if (user2_id_uuid.equals(user.getId())) {
                            String user1_firstname = resultSet1.getString("user1_firstname");
                            String user1_lastname = resultSet1.getString("user1_lastname");
                            String user1_username = resultSet1.getString("user1_username");
                            String user1_email = resultSet1.getString("user1_email");
                            String user1_password = resultSet1.getString("user1_password");

                            User user1 = new User(user1_firstname, user1_lastname, user1_username, user1_email, user1_password);
                            user1.setId(user1_id_uuid);
                            user.addFriend(user1);
                        }
                    }
                }
            }
            return users;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> save(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null!");
        }
        String insertSQL = "insert into users(id, firstname, lastname, email, password, username) values (?, ?, ?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(insertSQL);) {
            validator.validate(entity);
            statement.setObject(1, entity.getId(), Types.OTHER);
            statement.setString(2, entity.getFirstName());
            statement.setString(3, entity.getLastName());
            statement.setString(4, entity.getEmail());
            statement.setString(5, entity.getPassword());
            statement.setString(6, entity.getUsername());
            statement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> delete(UUID uuid) {
        String deleteSQL = "delete from users where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(deleteSQL);
        ) {
            statement.setObject(1, uuid, Types.OTHER);
            Optional<User> foundUser = getById(uuid);
            int response = 0;
            if (foundUser.isPresent()) {
                response = statement.executeUpdate();
            }
            return response == 0 ? Optional.empty() : foundUser;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> update(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null!");
        }
        String updateSQL = "update users set firstname = ?, lastname = ?, email = ?, password = ?, username = ? where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(updateSQL);
        ) {
            validator.validate(entity);
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setString(3, entity.getEmail());
            statement.setString(4, entity.getPassword());
            statement.setString(5, entity.getUsername());
            statement.setObject(6, entity.getId(), Types.OTHER);
            int response = statement.executeUpdate();
            return response == 0 ? Optional.empty() : Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
