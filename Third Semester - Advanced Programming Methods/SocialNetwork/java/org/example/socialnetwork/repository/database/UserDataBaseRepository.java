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

public class UserDataBaseRepository extends AbstractDataBaseRepository<Long, User> implements UserPaging{
    public UserDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator<User> validator) {
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

    private int countFriends(Long id){
        String statem = "SELECT COUNT(*) FROM getfriendshipinformation WHERE ((firstUserId=? OR secondUserId=?) AND status=?)";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(statem);
            statement.setLong(1, id);
            statement.setLong(2, id);
            statement.setString(3, "ACCEPTED");
            try{
                ResultSet resultSet = statement.executeQuery();
                return resultSet.next() ? resultSet.getInt(1) : 0;
            }catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private User getFriendFromStatement(ResultSet resultSet, Integer position) throws SQLException {
        User friend;
        if (position.equals(1)) {
            var idUser1 = resultSet.getLong("firstUserId");
            var firstNameUser1 = resultSet.getString("firstNameU1");
            var lastNameUser1 = resultSet.getString("lastNameU1");
            var usernameUser1 = resultSet.getString("usernameU1");
            var passwordUser1 = resultSet.getString("passwordU1");
            friend = new User(firstNameUser1, lastNameUser1, usernameUser1, passwordUser1);
            friend.setId(idUser1);
        } else {
            var idUser2 = resultSet.getLong("secondUserId");
            var firstNameUser2 = resultSet.getString("firstNameU2");
            var lastNameUser2 = resultSet.getString("lastNameU2");
            var usernameUser2 = resultSet.getString("usernameU2");
            var passwordUser2 = resultSet.getString("passwordU2");
            friend = new User(firstNameUser2, lastNameUser2, usernameUser2, passwordUser2);
            friend.setId(idUser2);
        }
        return friend;
    }

    @Override
    public Page<User> findAllOnPage(Pageable pageable, Long id) {
        String statem = "SELECT * FROM \"getfriendshipinformation\" WHERE ((firstUserId=? OR secondUserId=?) AND " +
                "status=?) LIMIT ? OFFSET ?";
        Map<Long, User> friendsMap = new HashMap<>();

        try{
            PreparedStatement statement = dataBaseAccess.createStatement(statem);
            statement.setLong(1, id);
            statement.setLong(2, id);
            statement.setString(3, "ACCEPTED");
            statement.setInt(4, pageable.getPageSize());
            statement.setInt(5,pageable.getPageNumber() * pageable.getPageSize());
            try(ResultSet resultSet = statement.executeQuery()) {
                Integer position = 0;
                while(resultSet.next()){
                    Long userId1 = resultSet.getLong("firstUserId");
                    Long userId2 = resultSet.getLong("secondUserId");
                    if(userId1.equals(id)){
                        position = 2;
                    }
                    if(userId2.equals(id)){
                        position = 1;
                    }
                    User friend = getFriendFromStatement(resultSet, position);
                    if(friend != null)
                        friendsMap.put(friend.getId(), friend);
                }
            }catch (SQLException e) {
                throw new RuntimeException(e);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Page<>(friendsMap.values(), countFriends(id));
    }

    private Optional<User> getUser(ResultSet resultSet, Long id) throws SQLException {
        String firstName = resultSet.getString("firstName");
        String lastName = resultSet.getString("lastName");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        User user = new User(firstName, lastName, username, password);
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
        String insertSql = "INSERT INTO " + tableName + " (firstName, lastName, username, password) VALUES (?, ?, ?, ?)";
        try {
            PreparedStatement statement = dataBaseAccess.createStatement(insertSql);
            statement.setString(1,entity.getFirstName());
            statement.setString(2,entity.getLastName());
            statement.setString(3,entity.getUsername());
            statement.setString(4,entity.getPassword());
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
            String deleteStatement = "DELETE FROM " + tableName + " WHERE id = ?";
            int response = 0;
            try{
                PreparedStatement statement = dataBaseAccess.createStatement(deleteStatement);
                statement.setLong(1, id);
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
        String updateStatement = "UPDATE " + tableName + " SET firstName = ?, lastName = ?, username = ?, password = ? WHERE id = ?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(updateStatement);
            statement.setString(1,entity.getFirstName());
            statement.setString(2,entity.getLastName());
            statement.setString(3,entity.getUsername());
            statement.setString(4,entity.getPassword());
            statement.setLong(5,entity.getId());
            int response = statement.executeUpdate();
            return response==0?Optional.of(entity):Optional.empty();
        }catch(SQLException e){
            throw new RuntimeException(e);
        }
    }
}
