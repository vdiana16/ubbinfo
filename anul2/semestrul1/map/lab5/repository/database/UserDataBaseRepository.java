package org.example.repository.database;

import org.example.domain.User;
import org.example.domain.validators.Validator;
import org.example.repository.database.util.AbstractDataBaseRepository;
import org.example.repository.database.util.DataBaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UserDataBaseRepository extends AbstractDataBaseRepository<Long, User> {
    public UserDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator<User> validator) {
        super(dataBaseAccess, tableName, validator);
    }

    private Optional<User> getUser(ResultSet resultSet, Long id) throws SQLException {
        String firstName = resultSet.getString("firstName");
        String lastName = resultSet.getString("lastName");
        User user = new User(firstName, lastName);
        user.setId(id);
        return Optional.of(user);
    }

    @Override
    public Optional<User> findOne(Long id) {
        if(id == null) {
            throw new IllegalArgumentException("id is null");
        }
        String findOneStatement = "SELECT * FROM " + tableName + " WHERE id = ?";
        try {
            PreparedStatement statement = dataBaseAccess.createStatement(findOneStatement);
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()){
                return getUser(resultSet, id);
            }
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<User> findAll() {
        String findAllStatement = "SELECT * FROM " + tableName;
        Set<User> users = new HashSet<>();
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(findAllStatement);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()){
                Long id = resultSet.getLong("id");
                users.add(getUser(resultSet, id).get());
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return users;
    }

    @Override
    public Optional<User> save(User entity) {
        if (entity == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        validator.validate(entity);
        String insertSql = "INSERT INTO " + tableName + " (firstName, lastName) VALUES (?, ?)";
        try {
            PreparedStatement statement = dataBaseAccess.createStatement(insertSql);
            statement.setString(1,entity.getFirstName());
            statement.setString(2,entity.getLastName());
            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<User> delete(Long id) {
        Optional<User> entity = findOne(id);
        if (id == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        else {
            String deleteStatement = "DELETE FROM " + tableName + " WHERE id="+id;
            int response = 0;
            try{
                PreparedStatement statement = dataBaseAccess.createStatement(deleteStatement);
                if(entity.isPresent()){
                    response = statement.executeUpdate();
                }
                return response==0?Optional.empty():entity;
            }catch (SQLException e){
                throw new RuntimeException(e);
            }
        }
    }

    @Override
    public Optional<User> update(User entity) {
        if(entity == null) {
            throw new IllegalArgumentException("entity cannot be null");
        }
        validator.validate(entity);
        String updateStatement = "UPDATE " + tableName + " SET firstName = ?, lastName = ? WHERE id = ?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(updateStatement);
            statement.setString(1,entity.getFirstName());
            statement.setString(2,entity.getLastName());
            statement.setLong(3,entity.getId());
            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }
}
