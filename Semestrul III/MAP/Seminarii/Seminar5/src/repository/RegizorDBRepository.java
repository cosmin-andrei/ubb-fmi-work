package repository;

import domain.Regizor;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class RegizorDBRepository implements Repository<Long, Regizor> {

    private String url;
    private String username;
    private String password;

    public RegizorDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Regizor> findOne(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Iterable<Regizor> findAll() {

        Set<Regizor> set = new HashSet<>();

        //le pun in try ca sa inchid resursele
        //putem pune try resources doar pt clasele care extind autocloseable
        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement statement = connection.prepareStatement("select * from regizori");
            ResultSet resultSet = statement.executeQuery();
            ){
            while(resultSet.next()){
                Long id = resultSet.getLong("id");
                String nume = resultSet.getString("nume");
                Regizor regizor = new Regizor(id,nume);
                set.add(regizor);
            }

            return set;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Regizor> save(Regizor entity) {
        return Optional.empty();
    }

    @Override
    public Optional<Regizor> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Regizor> update(Regizor entity) {
        return Optional.empty();
    }
}
