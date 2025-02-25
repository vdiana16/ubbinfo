package org.example.repository.database;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.domain.validators.Validator;
import org.example.repository.database.util.AbstractDataBaseRepository;
import org.example.repository.database.util.DataBaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipDataBaseRepository extends AbstractDataBaseRepository<Long, Friendship> {
    public FriendshipDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator<Friendship> validator) {
        super(dataBaseAccess, tableName, validator);
    }

    private void setDataInStatement(PreparedStatement statement, Friendship friendship) throws SQLException {
        statement.setLong(1, friendship.getUser1().getId());
        statement.setString(2, friendship.getUser1().getFirstName());
        statement.setString(3, friendship.getUser1().getLastName());
        statement.setLong(4, friendship.getUser2().getId());
        statement.setString(5, friendship.getUser2().getFirstName());
        statement.setString(6, friendship.getUser2().getLastName());
        statement.setTimestamp(7, Timestamp.valueOf(friendship.getDate()));
    }

    @Override
    public Optional<Friendship> findOne(Long id) {
        if(id == null){
            throw new IllegalArgumentException("Id cannot be null");
        }
        String findOneStatement = "SELECT * FROM " + tableName + " WHERE id = ?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(findOneStatement);
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();

            if(resultSet.next()) {
                return Optional.of(getFriendshipFromStatement(resultSet));
            }
            return Optional.empty();
        }catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private Friendship getFriendshipFromStatement(ResultSet resultSet) throws SQLException {
        var idFriendship = resultSet.getLong("id");

        var idUser1 = resultSet.getLong("firstUserId");
        var firstNameUser1 = resultSet.getString("firstUserFirstName");
        var lastNameUser1 = resultSet.getString("firstUserLastName");
        var user1 = new User(firstNameUser1, lastNameUser1);
        user1.setId(idUser1);

        var idUser2 = resultSet.getLong("secondUserId");
        var firstNameUser2 = resultSet.getString("secondUserFirstName");
        var lastNameUser2 = resultSet.getString("secondUserLastName");
        var user2 = new User(firstNameUser2, lastNameUser2);
        user2.setId(idUser2);

        Timestamp friendsFrom = resultSet.getTimestamp("friendsFrom");
        Friendship friendship = new Friendship(user1, user2, friendsFrom.toLocalDateTime());
        friendship.setId(idFriendship);

        return friendship;
    }

    @Override
    public Iterable<Friendship> findAll() {
        String findAllStatement = "SELECT * FROM" + tableName;
        Set<Friendship> friendships = new HashSet<>();
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(findAllStatement);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()){
                Friendship friendship = getFriendshipFromStatement(resultSet);
                friendships.add(friendship);
            }
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
        return friendships;
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        validator.validate(entity);
        String insertSql = "INSERT INTO" + tableName + "(firstUserId, firstUserFirstName, firstUserLastName, " +
                "secondUserId, secondUserFirstName, secondUserLastName, friendsFrom) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(insertSql);
            this.setDataInStatement(statement, entity);
            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Friendship> delete(Long id) {
        Optional<Friendship> entity = findOne(id);
        if (id == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        else{
            String deleteStatement = "DELETE FROM" + tableName + " WHERE id = ?";
            int response = 0;
            try{
                PreparedStatement statement = dataBaseAccess.createStatement(deleteStatement);
                statement.setLong(1, id);
                if(entity.isPresent()){
                    response = statement.executeUpdate();
                }
                return response==0? Optional.empty():entity;
            }catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        if(entity == null) {
            throw new IllegalArgumentException("entity cannot be null");
        }
        validator.validate(entity);
        String updateStatement = "UPDATE " + tableName + " SET " +
                "firstUserId = ?, firstUserFirstName = ?, firstUserLastName = ?, secondUserId = ?, secondUserFirstName = ?," +
                " secondUserLastName = ? friendsFrom = ?" + "WHERE id = ?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(updateStatement);
            this.setDataInStatement(statement, entity);
            statement.setLong(8, entity.getId());

            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
