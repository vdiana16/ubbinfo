using System.Configuration;
using System.Net.Sockets;
using System.Reflection;
using log4net;
using log4net.Config;
using TravelModel.model;
using TravelModel.model.validator;
using TravelNetworking.networking;
using TravelNetworking.networking.jsonprotocol;
using TravelPersistence.persistence.impl;
using TravelPersistence.persistence.interfaces;
using TravelServer.server;
using TravelServices.services;
using Thread = System.Threading.Thread;

namespace TravelServer;

class StartServer
{
    private static int DefaultPort = 55556;
    private static String DefaultIp = "127.0.0.1";
    private static readonly ILog logger = LogManager.GetLogger(typeof(StartServer));
    
    private static string GetConnectionStringByName(string name)
    {
        // Assume failure.
        string returnValue = null;

        // Look for the name in the connectionStrings section.
        ConnectionStringSettings settings =ConfigurationManager.ConnectionStrings[name];

        // If found, return the connection string.
        if (settings != null)
            returnValue = settings.ConnectionString;

        return returnValue;
    }

    public class JSonServer : ConcurrentServer
    {
        private ITravelServices server;
        private TravelClientJsonWorker worker;
        
        public JSonServer(string host, int port, ITravelServices server) : base(host, port)
        {
            this.server = server;
            logger.Info("Starting JSON server...");
        }

        protected override Thread createWorker(TcpClient tcpClient)
        {
            worker = new TravelClientJsonWorker(server, tcpClient);
            return new Thread(new ThreadStart(worker.run));
        }
    }
    
    static void Main(string[] args)
    {
        Console.WriteLine("Starting server...");
        var log = LogManager.GetRepository(Assembly.GetEntryAssembly());
        XmlConfigurator.Configure(log, new FileInfo("log4net.config"));
        
        logger.Info("Starting server...");
        logger.Info("Reading properties...");
        
        int port = DefaultPort;
        String ip = DefaultIp;
        String portT = ConfigurationManager.AppSettings["port"];

        if (portT == null)
        {
            logger.Debug("Port not set in properties file, using default port: " + DefaultPort);
        }
        else
        {
            bool result = Int32.TryParse(portT, out port);
            if (!result)
            {
                logger.Debug("Port is not a number, using default port: " + DefaultPort);
                port = DefaultPort;
            }
        }
        
        String ipT = ConfigurationManager.AppSettings["ip"];
        if (ipT == null)
        {
            logger.Debug("Ip not set in properties file, using default ip: " + DefaultIp);
        }
        
        logger.InfoFormat("Configuration Settings for database: {0}", GetConnectionStringByName("TravelAgency"));
        
        IDictionary<String, string> properties = new SortedList<String, String>();
        properties.Add("connectionString", GetConnectionStringByName("TravelAgency"));
        
        IValidator<Agent> agencyValidator = ValidatorFactory.GetInstance().CreateValidator<Agent>(ValidatorStrategy.Agent);
        IAgentRepository agentRepository = new AgentRepositoryImpl(properties, agencyValidator);
        
        IValidator<Reservation> reservationValidator = ValidatorFactory.GetInstance().CreateValidator<Reservation>(ValidatorStrategy.Reservation);
        IReservationRepository reservationRepository = new ReservationRepositoryImpl(properties, reservationValidator);
        
        IValidator<Tour> tourValidator = ValidatorFactory.GetInstance().CreateValidator<Tour>(ValidatorStrategy.Tour);
        ITourRepository tourRepository = new TourRepositoryImpl(properties, tourValidator);
        
        ITravelServices travelServices = new TravelServicesImpl(agentRepository, tourRepository, reservationRepository);
        
        logger.DebugFormat("Starting server on {0}:{1}", ip, port);
        JSonServer server = new JSonServer(ip, port, travelServices);
        server.Start();
        logger.Debug("Server started");
        Console.ReadLine();
    }
}