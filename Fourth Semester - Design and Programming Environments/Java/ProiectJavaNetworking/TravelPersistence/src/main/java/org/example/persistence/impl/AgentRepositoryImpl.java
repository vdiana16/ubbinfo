package org.example.persistence.impl;


import org.example.model.Agent;
import org.example.model.validator.Validator;
import org.example.persistence.interfaces.AgentRepository;
import org.example.persistence.utils.JdbcUtils;
import org.example.persistence.utils.RepositoryException;

import org.mindrot.jbcrypt.BCrypt;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;


public class AgentRepositoryImpl implements AgentRepository {
    private JdbcUtils jdbcUtils;
    private Validator<Agent> validator;

    public AgentRepositoryImpl(Properties properties, Validator<Agent> validator) {
        this.jdbcUtils = new JdbcUtils(properties);
        this.validator = validator;
    }

    private Agent getAgentFromSet(ResultSet result) throws SQLException {
        Integer id = result.getInt("id");
        String name = result.getString("name");
        String username = result.getString("username");
        String password = result.getString("password");
        Agent agent = new Agent(name, username, password);
        agent.setId(id);
        return agent;
    }

    @Override
    public Iterable<Agent> findAll(){
        Connection connection = jdbcUtils.getConnection();

        List<Agent> agents = new ArrayList<>();
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from agent")){
            try(ResultSet result = preparedStatement.executeQuery()){
                while (result.next()){
                    Agent agent = getAgentFromSet(result);
                    agents.add(agent);
                }
            }
        } catch (Exception e) {
            throw new RepositoryException("Error getting connection", e);
        }

        return agents;
    }

    @Override
    public Optional<Agent> findOne(Integer id) {
        Connection connection = jdbcUtils.getConnection();

        Agent agent = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from agent where id = ?")){
            preparedStatement.setInt(1, id);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    agent = getAgentFromSet(result);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error finding agent in database", e);
        }

        return Optional.ofNullable(agent);
    }

    private boolean isPasswordCorrect(String enteredPassword, String storedPasswordHash) {
        return BCrypt.checkpw(enteredPassword, storedPasswordHash);
    }

    @Override
    public Optional<Agent> findByUsername(String username, String password) {
        Connection connection = jdbcUtils.getConnection();

        Agent agent = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from agent where username = ?")){
            preparedStatement.setString(1, username);

            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    agent = getAgentFromSet(result);
                    String storedPasswordHash = agent.getPassword(); // presupunem că agent.getPassword() returnează hash-ul stocat
                    if (isPasswordCorrect(password, storedPasswordHash)) {
                        return Optional.of(agent);
                    }
                    return Optional.empty();
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error finding agent in database", e);
        }

        return Optional.ofNullable(agent);
    }

    @Override
    public Optional<Agent> save(Agent entity) {
        validator.validate(entity);
        if (findByUsername(entity.getUsername(), entity.getPassword()).isPresent()){
            throw new RepositoryException("This agent already exists");
        }

        // Criptează parola folosind bcrypt
        String encryptedPassword = BCrypt.hashpw(entity.getPassword(), BCrypt.gensalt());

        Connection connection = jdbcUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into agent (name, username, password) values (?, ?, ?)")){
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setString(2, entity.getUsername());
            preparedStatement.setString(3, encryptedPassword);
            int result = preparedStatement.executeUpdate();

            Optional<Agent> agentF = findByUsername(entity.getUsername(), entity.getPassword());
            entity.setId(agentF.get().getId());
        } catch (SQLException exception) {
            throw new RepositoryException("Error saving agent in database", exception);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Agent> delete(Integer integer) {
        if (integer == null || integer < 0){
            throw new RepositoryException("Agent id is null or negative");
        }

        Optional<Agent> agent = findOne(integer);
        if (agent.isEmpty()){
            throw new RepositoryException("This agent doesn't exists");
        }

        Connection connection = jdbcUtils.getConnection();

        try(PreparedStatement preparedStatement = connection.prepareStatement("delete from agent where id = ?")){
            preparedStatement.setInt(1, integer);

            int result = preparedStatement.executeUpdate();
        } catch (SQLException exception) {
            throw new RepositoryException("Error deleting agent in database", exception);
        }

        return agent;
    }

    @Override
    public Optional<Agent> update(Agent entity) {
        validator.validate(entity);
        if (findOne(entity.getId()).isEmpty()){
            throw new RepositoryException("This agent doesn't exists");
        }

        Connection connection = jdbcUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("update agent set name = ?, username = ?, password = ? where id = ?")){
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setString(2, entity.getUsername());
            preparedStatement.setString(3, entity.getPassword());
            preparedStatement.setInt(4, entity.getId());

            int result = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error updating agent in database", e);
        }

        return Optional.of(entity);
    }
}
