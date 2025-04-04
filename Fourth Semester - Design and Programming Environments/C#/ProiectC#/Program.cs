using System.Configuration;
using System.Xml;
using log4net;
using log4net.Config;
using TravelAgency;
using TravelAgency.model;
using TravelAgency.model.validator;
using TravelAgency.repository;
using TravelAgency.repository.database;
using TravelAgency.service;

class Program
{
    private static readonly ILog log = LogManager.GetLogger(typeof(Program));
     
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
    
    static void Main(string[] args)
    {
        string configPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "log4net.config");
        FileInfo fileInfo;

        try
        {
            fileInfo = new FileInfo(configPath);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
            throw;
        }
        
        XmlConfigurator.Configure(new FileInfo("log4net.config"));
        
        IDictionary<string, string> properties = new Dictionary<string, string>();
        properties.Add("connectionString", GetConnectionStringByName("TravelAgency"));

        IValidator<Agent> agencyValidator = ValidatorFactory.GetInstance().CreateValidator<Agent>(ValidatorStrategy.Agent);
        IAgentRepository agentRepository = new AgentRepositoryImpl(properties, agencyValidator);
        
        IValidator<Reservation> reservationValidator = ValidatorFactory.GetInstance().CreateValidator<Reservation>(ValidatorStrategy.Reservation);
        IReservationRepository reservationRepository = new ReservationRepositoryImpl(properties, reservationValidator);
        
        IValidator<Trip> tripValidator = ValidatorFactory.GetInstance().CreateValidator<Trip>(ValidatorStrategy.Trip);
        ITripRepository tripRepository = new TripRepositoryImpl(properties, tripValidator);
    
        Service service = new Service(agentRepository, reservationRepository, tripRepository);
        
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new LoginForm(service));
    }
}