using System.Configuration;
using System.Reflection;
using log4net;
using log4net.Config;
using TravelClient.client;
using TravelNetworking.networking.jsonprotocol;
using TravelServices.services;

namespace TravelClient;

public class StartClient
{
    private static int DEFAULT_PORT = 55556;
    private static String DEFAULT_IP = "127.0.0.1";
    
    private static readonly ILog logger = LogManager.GetLogger(typeof(StartClient));

    public static void Main(string[] args)
    {
        Console.WriteLine("Starting client...");
        var log = LogManager.GetRepository(Assembly.GetEntryAssembly());
        XmlConfigurator.Configure(log, new FileInfo("log4net.config"));
        
        logger.Info("Starting client...");
        logger.Info("Reading properties...");

        int port = DEFAULT_PORT;
        String ip = DEFAULT_IP;
        String portT = ConfigurationManager.AppSettings["port"];

        if (portT != null)
        {
            logger.DebugFormat("Port was not set, use default value {0}", DEFAULT_PORT);
        }
        else
        {
            bool result = Int32.TryParse(portT, out port);
            if (!result)
            {
                logger.DebugFormat("Port was not set, use default value {0}", DEFAULT_PORT);
                port = DEFAULT_PORT;
                logger.DebugFormat("Port {0}", port);
            }
        }
        
        String ipT = ConfigurationManager.AppSettings["ip"];
        if (ipT == null)
        {
            logger.DebugFormat("IP was not set, use default value {0}", DEFAULT_IP);
        }

        logger.DebugFormat("Starting client on {0}:{1}", ip, port);

        ITravelServices server = new ServerJsonProxy(ip, port);
        ApplicationConfiguration.Initialize();
        var loginForm = new LoginForm(server);
        Application.Run(loginForm);
    }
}