package org.example.socialnetwork.repository.database;

import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.FriendshipStatus;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.repository.database.util.AbstractDataBaseRepository;
import org.example.socialnetwork.repository.database.util.DataBaseAccess;
import org.example.socialnetwork.utils.paging.Page;
import org.example.socialnetwork.utils.paging.Pageable;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.*;

public class FriendshipDataBaseRepository extends AbstractDataBaseRepository<Long, Friendship>{
    public FriendshipDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator<Friendship> validator) {
        super(dataBaseAccess, tableName, validator);
    }


    private Friendship getFriendshipFromStatement(ResultSet resultSet) throws SQLException {
        var idFriendship = resultSet.getLong("id");

        var idUser1 = resultSet.getLong("firstUserId");
        var firstNameUser1 = resultSet.getString("firstNameU1");
        var lastNameUser1 = resultSet.getString("lastNameU1");
        var usernameUser1 = resultSet.getString("usernameU1");
        var passwordUser1 = resultSet.getString("passwordU1");
        var user1 = new User(firstNameUser1, lastNameUser1, usernameUser1,passwordUser1);
        user1.setId(idUser1);

        var idUser2 = resultSet.getLong("secondUserId");
        var firstNameUser2 = resultSet.getString("firstNameU2");
        var lastNameUser2 = resultSet.getString("lastNameU2");
        var usernameUser2 = resultSet.getString("usernameU2");
        var passwordUser2 = resultSet.getString("passwordU2");
        var user2 = new User(firstNameUser2, lastNameUser2, usernameUser2, passwordUser2);
        user2.setId(idUser2);

        String status = resultSet.getString("status");
        Timestamp friendsFrom = resultSet.getTimestamp("friendsFrom");
        Friendship friendship = new Friendship(user1, user2, friendsFrom.toLocalDateTime(), FriendshipStatus.valueOf(status));
        friendship.setId(idFriendship);

        return friendship;
    }

    @Override
    public Optional<Friendship> findOne(Long id) {
        if(id == null){
            throw new IllegalArgumentException("Id cannot be null");
        }
        String findOneStatement = "SELECT * FROM getfriendshipinformation WHERE id=?;";
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

    @Override
    public Iterable<Friendship> findAll() {
        String findAllStatement = "SELECT * FROM getfriendshipinformation";
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
        String insertSql = "INSERT INTO" + tableName + "(firstUserId, secondUserId, friendsFrom, status) VALUES (?, ?, ?, ?)";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(insertSql);
            statement.setLong(1,entity.getUser1().getId());
            statement.setLong(2,entity.getUser2().getId());
            statement.setTimestamp(3,Timestamp.valueOf(entity.getDate()));
            statement.setString(4,entity.getStatus().toString());
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
            String deleteStatement = "DELETE FROM " + tableName + " WHERE id = ?";
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
        String updateStatement = "UPDATE " + tableName + " SET  friendsFrom=?, status=?  WHERE " +
                "(firstUserId=? AND secondUserId=?) OR (firstUserId=? AND secondUserId=?);";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(updateStatement);
            statement.setTimestamp(1, Timestamp.valueOf(entity.getDate()));
            statement.setString(2, entity.getStatus().toString());
            statement.setLong(3, entity.getUser1().getId());
            statement.setLong(4, entity.getUser2().getId());
            statement.setLong(5, entity.getUser2().getId());
            statement.setLong(6, entity.getUser1().getId());

            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}

