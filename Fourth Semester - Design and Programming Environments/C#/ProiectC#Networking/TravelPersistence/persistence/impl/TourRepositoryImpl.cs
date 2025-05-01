using System.Data;
using log4net;

using TravelModel.model;
using TravelModel.model.validator;
using TravelPersistence.persistence.interfaces;
using TravelPersistence.persistence.utils;

namespace TravelPersistence.persistence.impl;

public class TourRepositoryImpl : ITourRepository
{
    private static readonly ILog log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    private IValidator<Tour>? _tourValidator;

    private IDictionary<String, String> properties;

    public TourRepositoryImpl(IDictionary<String, String> properties, IValidator<Tour>? tourValidator)
    {
        log.Info("Creating TourDatabaseRepository");

        this.properties = properties;
        this._tourValidator = tourValidator;
    }
    
    private Tour GetTourFromResult(IDataReader dataReader)
    {
        int id = Convert.ToInt32(dataReader["id"]);
        string destination = dataReader["destination"].ToString();
        string transportCompany = dataReader["transportCompany"].ToString();
        string departureDate = dataReader["departureDate"].ToString().Trim();
        double price = Convert.ToDouble(dataReader["price"]);
        int numberOfAvailableSeats = Convert.ToInt32(dataReader["numberOfAvailableSeats"]);

        DateTime departure = DateTime.ParseExact(departureDate, "yyyy-MM-dd HH:mm", System.Globalization.CultureInfo.InvariantCulture);
        
        Tour? tour = new Tour(destination, transportCompany, departure, price, numberOfAvailableSeats);
        tour.Id = id;
        return tour;
    }

    public Tour? FindOne(int id)
    {
        log.Info("Finding Tour");

        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Tour Id is null");
        }

        Tour? tour = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from tour where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;

            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    tour = GetTourFromResult(dataReader);
                    log.InfoFormat("Exiting FindOne Tour with value: " + tour);
                }
            }
        }

        log.InfoFormat("Exiting FindOne Tour with value: " + tour);
        return tour;
    }

    public IEnumerable<Tour> FindAll()
    {
        log.Info("Finding All Tours");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Tour> tours = new List<Tour>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from tour";

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Tour tour = GetTourFromResult(dataReader);
                    tours.Add(tour);
                }
            }
        }

        log.InfoFormat("Exiting FindAll tours with value: " + tours);
        return tours;
    }
    
    public Tour? FindTour(string destination, string transportCompany, DateTime departureDate, double price,
        int numberOfAvailableSeats)
    {
        log.Info("Finding Tour by all");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (destination == "" || transportCompany == "" || departureDate == null || price == null || numberOfAvailableSeats == null)
        {
            throw new RepositoryException("Agency destination or transport company or departure dates or price or numberOfAvailableSeats are required");
        }
        
        Tour? tour = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from tour where destination=@destionation and transportCompany=@transportCompany and departureDate=@departureDate and price=@price and numberOfAvailableSeats=@numberOfAvailableSeats";
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
                    tour = GetTourFromResult(dataReader);
                    log.InfoFormat("Exiting Find Tour with value: " + tour);
                    return tour;
                }
            }
        }
        log.InfoFormat("Exiting Find Tour with value: " + tour);
        return tour;
    }
    
     public Tour? Save(Tour tour)
    {
        log.Info("Saving Tour");
        IDbConnection connection = DBUtils.getConnection(properties);

        _tourValidator.Validate(tour);

        Tour? tourFound = FindTour(tour.Destination, tour.TransportCompany, tour.DepartureDate, tour.Price, tour.NumberOfAvailableSeats);
        if (tourFound != null)
        {
            log.InfoFormat("Tour already exists with value: " + tourFound);
            throw new RepositoryException("Tour already exists");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText =
                "insert into tour (destination, transportCompany, departureDate, price, numberOfAvailableSeats) values (@destination, @transportCompany, @departureDate, @price, @numberOfAvailableSeats)";
            IDbDataParameter destinationParameter = command.CreateParameter();
            destinationParameter.ParameterName = "@destination";
            destinationParameter.Value = tour.Destination;
            command.Parameters.Add(destinationParameter);
            
            IDbDataParameter transportParameter = command.CreateParameter();
            transportParameter.ParameterName = "@transportCompany";
            transportParameter.Value = tour.TransportCompany;
            command.Parameters.Add(transportParameter);
            
            IDbDataParameter departureDateParameter = command.CreateParameter();
            departureDateParameter.ParameterName = "@departureDate";
            departureDateParameter.Value = tour.DepartureDate.ToString("yyyy-MM-dd HH:mm");;
            command.Parameters.Add(departureDateParameter);
            
            IDbDataParameter priceParameter = command.CreateParameter();
            priceParameter.ParameterName = "@price";
            priceParameter.Value = tour.Price;
            command.Parameters.Add(priceParameter);
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = tour.NumberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            command.ExecuteNonQuery();

            Tour? tourF = FindTour(tour.Destination, tour.TransportCompany, tour.DepartureDate, tour.Price, tour.NumberOfAvailableSeats);
            tour.Id = tourF.Id;
            log.InfoFormat("Tour saved with value: " + tour);
        }
        return tour;
    }

    public Tour? Delete(int id)
    {
        log.Info("Deleting Tour");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Tour Id is null");
        }
        
        Tour? tourFound = FindOne(id);
        if (tourFound == null)
        {
            log.InfoFormat("Tour is not found");
            throw new RepositoryException("Tour is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "delete from tour where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);
        
            command.ExecuteNonQuery();

            log.InfoFormat("Tour deleted with value: " + tourFound);
        }

        return tourFound;
    }

    public Tour? Update(Tour tour)
    {
        log.Info("Updating Tour");
        IDbConnection connection = DBUtils.getConnection(properties);

        _tourValidator.Validate(tour);

        Tour? tourFound = FindOne(tour.Id);
        if (tourFound == null)
        { 
            log.InfoFormat("Tour is not found");
            throw new RepositoryException("Tour is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "update tour set destination=@destionation, transportCompany=@transportCompany, departureDate=@departureDate, price=@price, numberOfAvailableSeats=@numberOfAvailableSeats where id = @id";
            IDbDataParameter destinationParameter = command.CreateParameter();
            destinationParameter.ParameterName = "@destionation";
            destinationParameter.Value = tour.Destination;
            command.Parameters.Add(destinationParameter);
            
            IDbDataParameter transportParameter = command.CreateParameter();
            transportParameter.ParameterName = "@transportCompany";
            transportParameter.Value = tour.TransportCompany;
            command.Parameters.Add(transportParameter);
            
            IDbDataParameter departureDateParameter = command.CreateParameter();
            departureDateParameter.ParameterName = "@departureDate";
            departureDateParameter.Value = tour.DepartureDate.ToString("yyyy-MM-dd HH:mm");;
            command.Parameters.Add(departureDateParameter);
            
            IDbDataParameter priceParameter = command.CreateParameter();
            priceParameter.ParameterName = "@price";
            priceParameter.Value = tour.Price;
            command.Parameters.Add(priceParameter);
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = tour.NumberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = tour.Id;
            command.Parameters.Add(parameter);
            
            command.ExecuteNonQuery();
            
            log.InfoFormat("Tour added with value: " + tour);
        }

        return tour;
    }

    public Tour? UpdateSeats(int id, int seatsReserved)
    {
        log.Info("Updating Seats");
        IDbConnection connection = DBUtils.getConnection(properties);
        Tour? tourFound = FindOne(id);
        
        if (tourFound == null)
        { 
            log.InfoFormat("Tour is not found");
            throw new RepositoryException("Tour is not found");
        }

        using (var command = connection.CreateCommand())
        {
            int numberOfAvailableSeats = tourFound.NumberOfAvailableSeats - seatsReserved;
            command.CommandText = "update tour set numberOfAvailableSeats=@numberOfAvailableSeats where id = @id";
            
            IDbDataParameter numberOfAvailableSeatsParameter = command.CreateParameter();
            numberOfAvailableSeatsParameter.ParameterName = "@numberOfAvailableSeats";
            numberOfAvailableSeatsParameter.Value = numberOfAvailableSeats;
            command.Parameters.Add(numberOfAvailableSeatsParameter);

            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);
            
            command.ExecuteNonQuery();
            
            Tour? tourF = FindOne(id);
            log.InfoFormat("Tour added with id: " + id);
            return tourF;
        }

        return null;
    }

    public IEnumerable<Tour> FindToursByDestination(string destination)
    {
        log.Info("Finding Tours by destination");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Tour> tours = new List<Tour>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select * from tour where destination=@destination";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@destination";
            parameter.Value = destination;
            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Tour tour = GetTourFromResult(dataReader);
                    tours.Add(tour);
                }
            }
        }

        log.InfoFormat("Exiting FindAll tours with value: " + tours);
        return tours;
    }
}