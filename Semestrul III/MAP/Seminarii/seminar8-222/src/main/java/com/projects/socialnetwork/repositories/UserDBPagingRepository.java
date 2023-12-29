package com.projects.socialnetwork.repositories;


import com.projects.socialnetwork.models.User;
import com.projects.socialnetwork.repositories.paging.*;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;
import java.util.UUID;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class UserDBPagingRepository extends UserDBRepository  implements PagingRepository<UUID, User>
{


    public UserDBPagingRepository(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    public Page<User> findAll(Pageable pageable) {
//        Stream<User> result = StreamSupport.stream(this.getAll().spliterator()
//                        , false)
//                .skip((pageable.getPageNumber()-1)  * pageable.getPageSize())
//                .limit(pageable.getPageSize());
//        return new PageImplementation<>(pageable, result);

        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from users limit ? offset ?");

        ) {
            statement.setInt(1,pageable.getPageSize());
            statement.setInt(2,pageable.getPageSize() * (pageable.getPageNumber()-1));
            ResultSet resultSet = statement.executeQuery();
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
            }

            return new PageImplementation<User>(pageable,users.stream()) ;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }
}
