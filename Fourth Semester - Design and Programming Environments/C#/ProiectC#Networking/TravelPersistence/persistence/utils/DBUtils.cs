using System.Data;

namespace TravelPersistence.persistence.utils;

public class DBUtils
{
    private static IDbConnection _instance = null;

    public static IDbConnection getConnection(IDictionary<string, string> props)
    {
        if (_instance == null || _instance.State == System.Data.ConnectionState.Closed)
        {
            _instance = getNewConnection(props);
            _instance.Open();
        }
        return _instance;
    }

    private static IDbConnection getNewConnection(IDictionary<string, string> props)
    {
        return Connection.ConnectionFactory.getInstance().createConnection(props);
    }
}