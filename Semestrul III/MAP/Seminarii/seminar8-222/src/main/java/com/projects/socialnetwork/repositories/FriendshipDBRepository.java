package com.projects.socialnetwork.repositories;

import com.projects.socialnetwork.models.Friendship;
import com.projects.socialnetwork.models.User;
import com.projects.socialnetwork.validators.FriendshipValidator;
import com.projects.socialnetwork.validators.Validator;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;
import java.util.UUID;

public class FriendshipDBRepository implements Repository<UUID, Friendship> {

    private String url;
    private String username;
    private String password;
    private Validator<Friendship> validator;

    public FriendshipDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
        validator = new FriendshipValidator();
    }

    @Override
    public Optional<Friendship> getById(UUID uuid) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from friendships where id = ?")) {
            statement.setObject(1, uuid, Types.OTHER);
            ResultSet resultSet = statement.executeQuery();
            Friendship f = null;
            if (resultSet.next()) {
                UUID id = (UUID) resultSet.getObject("id");
                UUID id1 = (UUID) resultSet.getObject("user1_id");
                UUID id2 = (UUID) resultSet.getObject("user2_id");
                //Get the user with id1 and id2
                PreparedStatement statement1 = connection.prepareStatement("select * from users where id = ?");
                statement1.setObject(1, id1, Types.OTHER);
                ResultSet resultSet1 = statement1.executeQuery();
                if (!resultSet1.next())
                    return Optional.empty();
                String firstName1 = resultSet1.getString("firstname");
                String lastName1 = resultSet1.getString("lastname");
                String username1 = resultSet1.getString("username");
                String email1 = resultSet1.getString("email");
                String password1 = resultSet1.getString("password");
                //Get the user with id2
                PreparedStatement statement2 = connection.prepareStatement("select * from users where id = ?");
                statement2.setObject(1, id2, Types.OTHER);
                ResultSet resultSet2 = statement2.executeQuery();

                if (!resultSet2.next())
                    return Optional.empty();

                String firstName2 = resultSet2.getString("firstname");
                String lastName2 = resultSet2.getString("lastname");
                String username2 = resultSet2.getString("username");
                String email2 = resultSet2.getString("email");
                String password2 = resultSet2.getString("password");
                User u1 = new User(firstName1, lastName1, username1, email1, password1);
                u1.setId(id1);
                User u2 = new User(firstName2, lastName2, username2, email2, password2);
                u2.setId(id2);
                f = new Friendship(u1, u2);
                f.setId(id);
            }
            return Optional.ofNullable(f);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Friendship> getAll() {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("select * from friendships")) {

            Set<Friendship> friendships = new HashSet<>();
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                UUID id = (UUID) resultSet.getObject("id");
                UUID id1 = (UUID) resultSet.getObject("user1_id");
                UUID id2 = (UUID) resultSet.getObject("user2_id");
                LocalDateTime friendsSince = resultSet.getObject("friend_since", LocalDateTime.class);
                //Get the user with id1 and id2
                PreparedStatement statement1 = connection.prepareStatement("select * from users where id = ?");
                statement1.setObject(1, id1, Types.OTHER);
                ResultSet resultSet1 = statement1.executeQuery();
                if (!resultSet1.next())
                    return null;
                String firstName1 = resultSet1.getString("firstname");
                String lastName1 = resultSet1.getString("lastname");
                String username1 = resultSet1.getString("username");
                String email1 = resultSet1.getString("email");
                String password1 = resultSet1.getString("password");
                //Get the user with id2
                PreparedStatement statement2 = connection.prepareStatement("select * from users where id = ?");
                statement2.setObject(1, id2, Types.OTHER);
                ResultSet resultSet2 = statement2.executeQuery();
                if (!resultSet2.next())
                    return null;
                String firstName2 = resultSet2.getString("firstname");
                String lastName2 = resultSet2.getString("lastname");
                String username2 = resultSet2.getString("username");
                String email2 = resultSet2.getString("email");
                String password2 = resultSet2.getString("password");
                User u1 = new User(firstName1, lastName1, username1, email1, password1);
                u1.setId(id1);
                User u2 = new User(firstName2, lastName2, username2, email2, password2);
                u2.setId(id2);
                Friendship f = new Friendship(u1, u2,friendsSince);
                f.setId(id);
                friendships.add(f);
            }
            return friendships;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null");
        }
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("insert into friendships (id,user1_id,user2_id,friend_since) values (?,?,?,?)")) {
            validator.validate(entity);
            statement.setObject(1, entity.getId(), Types.OTHER);
            statement.setObject(2, entity.getUser1().getId(), Types.OTHER);
            statement.setObject(3, entity.getUser2().getId(), Types.OTHER);
            statement.setObject(4,entity.getFriendsSince());
            statement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> delete(UUID uuid) {
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("delete from friendships where id = ?")) {
            statement.setObject(1, uuid, Types.OTHER);
            Optional<Friendship> foundFriendship = getById(uuid);
            int response = 0;
            if (foundFriendship.isPresent()) {
                response = statement.executeUpdate();
            }
            return response == 0 ? Optional.empty() : foundFriendship;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity must not be null");
        }
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("update friendships set user1_id = ?, user2_id = ? where id = ?")) {
            validator.validate(entity);
            statement.setObject(1, entity.getUser1().getId(), Types.OTHER);
            statement.setObject(2, entity.getUser2().getId(), Types.OTHER);
            statement.setObject(3, entity.getId(), Types.OTHER);
            statement.executeUpdate();
            int response = statement.executeUpdate();
            return response == 0 ? Optional.empty() : Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
