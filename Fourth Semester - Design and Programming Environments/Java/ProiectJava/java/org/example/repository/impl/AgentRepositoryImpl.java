package org.example.repository.impl;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.exception.RepositoryException;
import org.example.modul.Agent;
import org.example.modul.validator.Validator;
import org.example.repository.interfaces.AgentRepository;
import org.example.repository.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

import org.mindrot.jbcrypt.BCrypt;


public class AgentRepositoryImpl implements AgentRepository {
    private JdbcUtils jdbcUtils;
    private Validator<Agent> validator;
    private static final Logger logger = LogManager.getLogger();

    public AgentRepositoryImpl(Properties properties, Validator<Agent> validator) {
        logger.info("Initializing AgentDatabaseRepository with properties: {}", properties);

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
    public Iterable<Agent> findAll() {
        logger.traceEntry("Finding all agents");

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
            logger.error(e);
            throw new RepositoryException("Error getting connection", e);
        }

        logger.traceExit("Found agents {}", agents);
        return agents;
    }

    @Override
    public Optional<Agent> findOne(Integer id) {
        logger.traceEntry("Finding agent with id: {}", id);

        Connection connection = jdbcUtils.getConnection();

        Agent agent = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from agent where id = ?")){
            preparedStatement.setInt(1, id);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    agent = getAgentFromSet(result);
                    logger.trace("Found agent: {}", agent);
                }
                else {
                    logger.warn("No agent found with id {}", id);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error finding agent in database", e);
        }

        logger.traceExit();
        return Optional.ofNullable(agent);
    }

    private boolean isPasswordCorrect(String enteredPassword, String storedPasswordHash) {
        return BCrypt.checkpw(enteredPassword, storedPasswordHash);
    }

    @Override
    public Optional<Agent> findByUsername(String username, String password) {
        logger.traceEntry("Finding agent with username {} and password {}", username);

        Connection connection = jdbcUtils.getConnection();

        Agent agent = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from agent where username = ?")){
            preparedStatement.setString(1, username);

            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    agent = getAgentFromSet(result);
                    logger.trace("Found agent: {}", agent);
                    String storedPasswordHash = agent.getPassword(); // presupunem că agent.getPassword() returnează hash-ul stocat
                    if (isPasswordCorrect(password, storedPasswordHash)) {
                        logger.trace("Password is correct for agent: {}", agent);
                        return Optional.of(agent);
                    } else {
                        logger.warn("Incorrect password for agent: {}", username);
                        return Optional.empty();
                    }
                }
                else {
                    logger.warn("No agent found with username {}", username);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error finding agent in database", e);
        }

        logger.traceExit();
        return Optional.ofNullable(agent);
    }

    @Override
    public Optional<Agent> save(Agent entity) {
        logger.traceEntry("Saving agent {}", entity);

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

            if(result == 0) {
                logger.warn("Failed to save agent: {}", entity);
            }
            else {
                Optional<Agent> agentF = findByUsername(entity.getUsername(), entity.getPassword());
                entity.setId(agentF.get().getId());
                logger.trace("Successfully saved agent {}", entity);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error saving agent in database", exception);
        }

        logger.traceExit();
        return Optional.of(entity);
    }

    @Override
    public Optional<Agent> delete(Integer integer) {
        logger.traceEntry("Deleting agent with id: {}", integer);

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
            if(result == 0) {
                logger.warn("Failed to delete agent {}", agent);
            }
            else {
                logger.trace("Successfully deleted agent {}", agent);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error deleting agent in database", exception);
        }

        logger.traceExit();
        return agent;
    }

    @Override
    public Optional<Agent> update(Agent entity) {
        logger.traceEntry("Updating agent {}", entity);

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
            if(result == 0) {
                logger.warn("Failed to update agent {}", entity);
            }
            else {
                logger.trace("Successfully updated agent {}", entity);
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error updating agent in database", e);
        }

        logger.traceExit();
        return Optional.of(entity);
    }
}
