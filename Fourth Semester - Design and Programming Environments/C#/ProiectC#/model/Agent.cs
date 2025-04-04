namespace TravelAgency.model;

public class Agent: Entity<int>
{
    private string _name;
    private string _username;
    private string _password;

    public Agent(string name, string username, string password)
    {
        this._name = name;
        this._username = username;
        this._password = password;
    }

    public string Name
    {
        get => _name;
        set => _name = value;
    }

    public string Username
    {
        get => _username;
        set => _username = value;
    }

    public string Password
    {
        get => _password;
        set => _password = value;
    }
    
    public override string ToString()
    {
        return $"Agent Name: {_name}, Username: {_username}, Password: {_password}";
    }

    public override bool Equals(object? obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;
        Agent other = (Agent)obj;
        return _name == other._name && _username == other._username && _password == other._password;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(_name, _username, _password);
    }
        
}