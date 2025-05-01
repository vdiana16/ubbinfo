using System.Data;
using log4net;
using TravelModel.model;
using TravelModel.model.validator;
using TravelPersistence.persistence.interfaces;
using TravelPersistence.persistence.utils;

namespace TravelPersistence.persistence.impl;


public class AgentRepositoryImpl : IAgentRepository
{
    private static readonly ILog log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    private IValidator<Agent>? _agentValidator;

    private IDictionary<String, String> properties;

    public AgentRepositoryImpl(IDictionary<String, String> properties, IValidator<Agent>? agentValidator)
    {
        log.Info("Creating AgentDatabaseRepository");

        this.properties = properties;
        this._agentValidator = agentValidator;
    }

    private Agent GetAgentFromResult(IDataReader dataReader)
    {
        int id = Convert.ToInt32(dataReader["id"]);
        string agentName = dataReader["name"].ToString();
        string username = dataReader["username"].ToString();
        string password = dataReader["password"].ToString();

        Agent? agent = new Agent(agentName, username, password);
        agent.Id = id;
        return agent;
    }

    public Agent? FindOne(int id)
    {
        log.Info("Finding Agent");

        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Agent Id is null");
        }

        Agent? agent = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from agent where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;

            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    agent = GetAgentFromResult(dataReader);
                    log.InfoFormat("Exiting FindOne with value: " + agent);
                    return agent;
                }
            }
        }

        log.InfoFormat("Exiting FindOne with value: " + agent);
        return agent;
    }

    public IEnumerable<Agent> FindAll()
    {
        log.Info("Finding All Agencies");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Agent> agencies = new List<Agent>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from agent";

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Agent agent = GetAgentFromResult(dataReader);
                    agencies.Add(agent);
                }
            }
        }

        log.InfoFormat("Exiting FindAll agencies with value: " + agencies);
        return agencies;
    }

    public Agent? FindByUsername(string username, string password)
    {
        log.Info("Finding Agent by username" + username);
        IDbConnection connection = DBUtils.getConnection(properties);

        if (username == "" || password == "")
        {
            throw new RepositoryException("Agent Username or password is empty");
        }

        Agent? agent = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from agent where username = @username";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@username";
            parameter.Value = username;
            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    agent = GetAgentFromResult(dataReader);
                    log.InfoFormat("Exiting FindByUsername Agent with value: " + agent);

                    bool isPasswordValid = BCrypt.Net.BCrypt.Verify(password, agent.Password);
                    if (!isPasswordValid)
                    {
                        log.InfoFormat("Exiting FindByUsername Agent with value: " + agent);
                        throw new RepositoryException("Agent password is invalid");
                    }

                    return agent;
                }
            }
        }

        log.InfoFormat("Exiting FindByUsername Agent with value: " + agent);
        return agent;
    }

    public Agent? Save(Agent agent)
    {
        log.Info("Saving Agent");
        IDbConnection connection = DBUtils.getConnection(properties);

        _agentValidator.Validate(agent);

        Agent? agentFound = FindByUsername(agent.Username, agent.Password);
        if (agentFound != null)
        {
            log.InfoFormat("Agent already exists with value: " + agentFound);
            throw new RepositoryException("Agent already exists");
        }

        string hashedPassword = BCrypt.Net.BCrypt.HashPassword(agent.Password);

        using (var command = connection.CreateCommand())
        {
            command.CommandText =
                "insert into agent(name, username, password) values (@name, @username, @password)";
            IDbDataParameter agNameParameter = command.CreateParameter();
            agNameParameter.ParameterName = "@name";
            agNameParameter.Value = agent.Name;
            command.Parameters.Add(agNameParameter);

            IDbDataParameter usernameParameter = command.CreateParameter();
            usernameParameter.ParameterName = "@username";
            usernameParameter.Value = agent.Username;
            command.Parameters.Add(usernameParameter);

            IDbDataParameter passwordParameter = command.CreateParameter();
            passwordParameter.ParameterName = "@password";
            passwordParameter.Value = hashedPassword;
            command.Parameters.Add(passwordParameter);

            command.ExecuteNonQuery();

            Agent? agentF = FindByUsername(agent.Username, agent.Password);
            agent.Id = agentF.Id;
            log.InfoFormat("Agent saved with value: " + agent);
        }

        return agent;
    }

    public Agent? Delete(int id)
    {
        log.Info("Deleting Agent");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Agent Id is null");
        }

        Agent? agentFound = FindOne(id);
        if (agentFound == null)
        {
            log.InfoFormat("Agent is not found");
            throw new RepositoryException("Agent is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "delete from agent where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);

            command.ExecuteNonQuery();

            log.InfoFormat("Agent deleted with value: " + agentFound);
        }

        return agentFound;
    }

    public Agent? Update(Agent agent)
    {
        log.Info("Updating Agent");
        IDbConnection connection = DBUtils.getConnection(properties);

        _agentValidator.Validate(agent);

        Agent? agentFound = FindOne(agent.Id);
        if (agentFound == null)
        {
            log.InfoFormat("Agent is not found");
            throw new RepositoryException("Agent is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText =
                "update agent set name = @name, username = @username, password = @password where id = @id";
            IDbDataParameter agNameParameter = command.CreateParameter();
            agNameParameter.ParameterName = "@name";
            agNameParameter.Value = agent.Name;
            command.Parameters.Add(agNameParameter);

            IDbDataParameter usernameParameter = command.CreateParameter();
            usernameParameter.ParameterName = "@username";
            usernameParameter.Value = agent.Username;
            command.Parameters.Add(usernameParameter);

            IDbDataParameter passwordParameter = command.CreateParameter();
            passwordParameter.ParameterName = "@password";
            passwordParameter.Value = agent.Password;
            command.Parameters.Add(passwordParameter);

            IDbDataParameter idParameter = command.CreateParameter();
            idParameter.ParameterName = "@id";
            idParameter.Value = agent.Id;
            command.Parameters.Add(idParameter);

            command.ExecuteNonQuery();

            log.InfoFormat("Agent added with value: " + agent);
        }

        return agent;
    }
}