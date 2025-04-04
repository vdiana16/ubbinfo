using System.Data;
using log4net;
using TravelAgency.exception;
using TravelAgency.model;
using TravelAgency.model.validator;

namespace TravelAgency.repository.database;

public class TripRepositoryImpl : ITripRepository
{
    private static readonly ILog log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    private IValidator<Trip>? _tripValidator;

    private IDictionary<String, String> properties;

    public TripRepositoryImpl(IDictionary<String, String> properties, IValidator<Trip>? tripValidator)
    {
        log.Info("Creating TripDatabaseRepository");

        this.properties = properties;
        this._tripValidator = tripValidator;
    }
    
    private Trip GetTripFromResult(IDataReader dataReader)
    {
        int id = Convert.ToInt32(dataReader["id"]);
        string destination = dataReader["destination"].ToString();
        string transportCompany = dataReader["transportCompany"].ToString();
        string departureDate = dataReader["departureDate"].ToString().Trim();
        double price = Convert.ToDouble(dataReader["price"]);
        int numberOfAvailableSeats = Convert.ToInt32(dataReader["numberOfAvailableSeats"]);

        DateTime departure = DateTime.ParseExact(departureDate, "yyyy-MM-dd HH:mm", System.Globalization.CultureInfo.InvariantCulture);
        
        Trip? trip = new Trip(destination, transportCompany, departure, price, numberOfAvailableSeats);
        trip.Id = id;
        return trip;
    }

    public Trip? FindOne(int id)
    {
        log.Info("Finding Trip");

        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Trip Id is null");
        }

        Trip? trip = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from trip where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;

            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    trip = GetTripFromResult(dataReader);
                    log.InfoFormat("Exiting FindOne Trip with value: " + trip);
                }
            }
        }

        log.InfoFormat("Exiting FindOne Trip with value: " + trip);
        return trip;
    }

    public IEnumerable<Trip> FindAll()
    {
        log.Info("Finding All Trips");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Trip> trips = new List<Trip>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from trip";

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Trip trip = GetTripFromResult(dataReader);
                    trips.Add(trip);
                }
            }
        }

        log.InfoFormat("Exiting FindAll trips with value: " + trips);
        return trips;
    }
    
    public Trip? FindTrip(string destination, string transportCompany, DateTime departureDate, double price,
        int numberOfAvailableSeats)
    {
        log.Info("Finding Trip by all");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (destination == "" || transportCompany == "" || departureDate == null || price == null || numberOfAvailableSeats == null)
        {
            throw new RepositoryException("Agency destination or transport company or departure dates or price or numberOfAvailableSeats are required");
        }
        
        Trip? trip = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from trip where destination=@destionation and transportCompany=@transportCompany and departureDate=@departureDate and price=@price and numberOfAvailableSeats=@numberOfAvailableSeats";
            IDbDataParameter destinationParameter = command.CreateParameter();
            destinationParameter.ParameterName = "@destionation";
            destinationParameter.Value = destination;
            command.Parameters.Add(destinationParameter);
            
            IDbDataParameter transportParameter = command.CreateParameter();
            transportParameter.ParameterName = "@transportCompany";
            transportParameter.Value = transportCompany;
            command.Parameters.Add(transportParameter);
            
            IDbDataParameter departureDateParameter = command.CreateParameter();
            departureDateParameter.ParameterName = "@departureDate";
            departureDateParameter.Value = departureDate.ToString("yyyy-MM-dd HH:mm");;
            command.Parameters.Add(departureDateParameter);
            
            IDbDataParameter priceParameter = command.CreateParameter();
            priceParameter.ParameterName = "@price";
            priceParameter.Value = price;
            command.Parameters.Add(priceParameter);
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = numberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    trip = GetTripFromResult(dataReader);
                    log.InfoFormat("Exiting Find Trip with value: " + trip);
                    return trip;
                }
            }
        }
        log.InfoFormat("Exiting Find Trip with value: " + trip);
        return trip;
    }
    
     public Trip? Save(Trip trip)
    {
        log.Info("Saving Trip");
        IDbConnection connection = DBUtils.getConnection(properties);

        _tripValidator.Validate(trip);

        Trip? tripFound = FindTrip(trip.Destination, trip.TransportCompany, trip.DepartureDate, trip.Price, trip.NumberOfAvailableSeats);
        if (tripFound != null)
        {
            log.InfoFormat("Trip already exists with value: " + tripFound);
            throw new RepositoryException("Trip already exists");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText =
                "insert into trip (destination, transportCompany, departureDate, price, numberOfAvailableSeats) values (@destination, @transportCompany, @departureDate, @price, @numberOfAvailableSeats)";
            IDbDataParameter destinationParameter = command.CreateParameter();
            destinationParameter.ParameterName = "@destination";
            destinationParameter.Value = trip.Destination;
            command.Parameters.Add(destinationParameter);
            
            IDbDataParameter transportParameter = command.CreateParameter();
            transportParameter.ParameterName = "@transportCompany";
            transportParameter.Value = trip.TransportCompany;
            command.Parameters.Add(transportParameter);
            
            IDbDataParameter departureDateParameter = command.CreateParameter();
            departureDateParameter.ParameterName = "@departureDate";
            departureDateParameter.Value = trip.DepartureDate.ToString("yyyy-MM-dd HH:mm");;
            command.Parameters.Add(departureDateParameter);
            
            IDbDataParameter priceParameter = command.CreateParameter();
            priceParameter.ParameterName = "@price";
            priceParameter.Value = trip.Price;
            command.Parameters.Add(priceParameter);
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = trip.NumberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            command.ExecuteNonQuery();

            Trip? tripF = FindTrip(trip.Destination, trip.TransportCompany, trip.DepartureDate, trip.Price, trip.NumberOfAvailableSeats);
            trip.Id = tripF.Id;
            log.InfoFormat("Trip saved with value: " + trip);
        }
        return trip;
    }

    public Trip? Delete(int id)
    {
        log.Info("Deleting Trip");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Trip Id is null");
        }
        
        Trip? tripFound = FindOne(id);
        if (tripFound == null)
        {
            log.InfoFormat("Trip is not found");
            throw new RepositoryException("Trip is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "delete from trip where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);
        
            command.ExecuteNonQuery();

            log.InfoFormat("Trip deleted with value: " + tripFound);
        }

        return tripFound;
    }

    public Trip? Update(Trip trip)
    {
        log.Info("Updating Trip");
        IDbConnection connection = DBUtils.getConnection(properties);

        _tripValidator.Validate(trip);

        Trip? tripFound = FindOne(trip.Id);
        if (tripFound == null)
        { 
            log.InfoFormat("Trip is not found");
            throw new RepositoryException("Trip is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "update trip set destination=@destionation, transportCompany=@transportCompany, departureDate=@departureDate, price=@price, numberOfAvailableSeats=@numberOfAvailableSeats where id = @id";
            IDbDataParameter destinationParameter = command.CreateParameter();
            destinationParameter.ParameterName = "@destionation";
            destinationParameter.Value = trip.Destination;
            command.Parameters.Add(destinationParameter);
            
            IDbDataParameter transportParameter = command.CreateParameter();
            transportParameter.ParameterName = "@transportCompany";
            transportParameter.Value = trip.TransportCompany;
            command.Parameters.Add(transportParameter);
            
            IDbDataParameter departureDateParameter = command.CreateParameter();
            departureDateParameter.ParameterName = "@departureDate";
            departureDateParameter.Value = trip.DepartureDate.ToString("yyyy-MM-dd HH:mm");;
            command.Parameters.Add(departureDateParameter);
            
            IDbDataParameter priceParameter = command.CreateParameter();
            priceParameter.ParameterName = "@price";
            priceParameter.Value = trip.Price;
            command.Parameters.Add(priceParameter);
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = trip.NumberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = trip.Id;
            command.Parameters.Add(parameter);
            
            command.ExecuteNonQuery();
            
            log.InfoFormat("Trip added with value: " + trip);
        }

        return trip;
    }

    public Trip? UpdateSeats(int id, int seatsReserved)
    {
        log.Info("Updating Seats");
        IDbConnection connection = DBUtils.getConnection(properties);
        Trip? tripFound = FindOne(id);
        
        if (tripFound == null)
        { 
            log.InfoFormat("Trip is not found");
            throw new RepositoryException("Trip is not found");
        }

        using (var command = connection.CreateCommand())
        {
            int numberOfAvailableSeats = tripFound.NumberOfAvailableSeats - seatsReserved;
            command.CommandText = "update trip set numberOfAvailableSeats=@numberOfAvailableSeats where id = @id";
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = numberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);
            
            command.ExecuteNonQuery();
            
            Trip? tripF = FindOne(id);
            log.InfoFormat("Trip added with id: " + id);
            return tripF;
        }

        return null;
    }

    public IEnumerable<Trip> FindTripsByDestination(string destination)
    {
        log.Info("Finding Trips by destination");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Trip> trips = new List<Trip>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from trip where destination=@destination";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@destination";
            parameter.Value = destination;
            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Trip trip = GetTripFromResult(dataReader);
                    trips.Add(trip);
                }
            }
        }

        log.InfoFormat("Exiting FindAll trips with value: " + trips);
        return trips;
    }
}