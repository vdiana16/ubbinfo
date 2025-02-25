package org.example.socialnetwork.repository.database;

import org.example.socialnetwork.domain.Message;
import org.example.socialnetwork.domain.User;
import org.example.socialnetwork.domain.validators.Validator;
import org.example.socialnetwork.repository.database.util.AbstractDataBaseRepository;
import org.example.socialnetwork.repository.database.util.DataBaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.*;

public class MessageDataBaseRepository extends AbstractDataBaseRepository<Long, Message> {
    public MessageDataBaseRepository(DataBaseAccess dataBaseAccess, String tableName, Validator validator) {
        super(dataBaseAccess, tableName, validator);
    }

    private Optional<Message> getMessage(ResultSet resultSet, Long id) throws SQLException {
        try{
            String firstNameSend = resultSet.getString("firstNameSend");
            String lastNameSend = resultSet.getString("lastNameSend");
            String usernameSend = resultSet.getString("usernameSend");
            String passwordSend = resultSet.getString("passwordSend");
            User from = new User(firstNameSend, lastNameSend, usernameSend, passwordSend);
            from.setId(resultSet.getLong("idSender"));

            String firstNameRecv = resultSet.getString("firstNameRecv");
            String lastNameRecv = resultSet.getString("lastNameRecv");
            String usernameRecv = resultSet.getString("usernameRecv");
            String passwordRecv = resultSet.getString("passwordRecv");
            User to = new User(firstNameRecv, lastNameRecv, usernameRecv, passwordRecv);
            to.setId(resultSet.getLong("idReceiver"));

            String message = resultSet.getString("message");
            LocalDateTime timestamp = resultSet.getTimestamp("dateSend").toLocalDateTime();
            Long replyingTo = resultSet.getLong("replyingToId");

            Message m = new Message(from, to, message, timestamp, replyingTo);
            m.setId(id);
            return Optional.of(m);
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Message> findOne(Long id) {
        if(id == null){
            throw new IllegalArgumentException("Id cannot be null");
        }
        String findOneStatment = "SELECT * FROM getMessageInformation WHERE id=?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(findOneStatment);
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()){
                return getMessage(resultSet, id);
            }
            return Optional.empty();
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
    }

    @Override
    public Iterable<Message> findAll() {
        List<Message> messages = new ArrayList<>();
        String findAllStatment = "SELECT * FROM getMessageInformation";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(findAllStatment);
            ResultSet resultSet = statement.executeQuery();
            while(resultSet.next()){
                Long idMessage = resultSet.getLong("id");
                Optional<Message> optionalMessage = getMessage(resultSet, idMessage);
                optionalMessage.ifPresent(messages::add);
            }
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
        return messages;
    }

    @Override
    public Optional<Message> save(Message entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity cannot be null");
        }
        String insertStatement = "INSERT INTO " + tableName + " (message, dateSend, replyingToId, idReceiver, idSender) VALUES (?, ?, ?, ?, ?) RETURNING id";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(insertStatement);
            statement.setString(1, entity.getMessage());
            statement.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            statement.setLong(3, entity.getReplyingTo());
            statement.setLong(4, entity.getTo().getId());
            statement.setLong(5, entity.getFrom().getId());

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long id = resultSet.getLong("id");
                entity.setId(id);
                return Optional.of(entity);
            }
            return Optional.empty();
        }catch (SQLException e){
            throw new RuntimeException(e);
        }

    }

    @Override
    public Optional<Message> delete(Long id) {
        Optional<Message> entity = findOne(id);
        if(id != null){
            String deleteStatement = "DELETE FROM " + tableName + " WHERE id=?";
            int response = 0;
            try{
                PreparedStatement statement = dataBaseAccess.createStatement(deleteStatement);
                if(entity.isPresent()){
                    statement.setLong(1, id);
                    response = statement.executeUpdate();
                }
                return response==0?Optional.empty():entity;
            }catch (SQLException e){
                throw new RuntimeException(e);
            }
        } else{
            throw new IllegalArgumentException("Id cannot be null");
        }
    }

    @Override
    public Optional<Message> update(Message entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entity cannot be null");
        }

        String updateStatement = "UPDATE " + tableName + " SET message=?, dateSend=?, idReceiver=?, idSender=?  WHERE id=?";
        try{
            PreparedStatement statement = dataBaseAccess.createStatement(updateStatement);
            statement.setString(1, entity.getMessage());
            statement.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            statement.setLong(3, entity.getReplyingTo());
            statement.setLong(4, entity.getTo().getId());
            statement.setLong(5, entity.getFrom().getId());
            statement.setLong(6, entity.getId());

            int response = statement.executeUpdate();
            return response==0?Optional.empty():Optional.of(entity);
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
    }
}
