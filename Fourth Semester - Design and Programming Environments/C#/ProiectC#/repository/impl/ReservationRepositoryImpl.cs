using TravelAgency.model;
using System.Data;
using log4net;
using TravelAgency.exception;
using TravelAgency.model.validator;

namespace TravelAgency.repository.database;

public class ReservationRepositoryImpl : IReservationRepository
{
    private static readonly ILog log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    private IValidator<Reservation>? _reservationValidator;

    private IDictionary<String, String> properties;

    public ReservationRepositoryImpl(IDictionary<String, String> properties, IValidator<Reservation>? reservationValidator)
    {
        log.Info("Creating ReservationDatabaseRepository");

        this.properties = properties;
        this._reservationValidator = reservationValidator;
    }
    
    private Reservation GetReservationFromResult(IDataReader dataReader)
    {
        int id = Convert.ToInt32(dataReader["id"]);
        int numberOfReservedSeats = Convert.ToInt32(dataReader["numberOfReservedSeats"]);
        
        int tripId = Convert.ToInt32(dataReader["tripId"]);
        string destination = dataReader["destination"].ToString();
        string transportCompany = dataReader["transportCompany"].ToString();
        string departureDate = dataReader["departureDate"].ToString();
        double price = Convert.ToDouble(dataReader["price"]);
        int numberOfAvailableSeats = Convert.ToInt32(dataReader["numberOfAvailableSeats"]);
        DateTime departure = DateTime.ParseExact(departureDate, "yyyy-MM-dd HH:mm", System.Globalization.CultureInfo.InvariantCulture);
        Trip? trip = new Trip(destination, transportCompany, departure, price, numberOfAvailableSeats);
        trip.Id = tripId;
        
        string clientName = dataReader["clientName"].ToString();
        string clientContact = dataReader["clientContact"].ToString();
        
        Reservation? reservation = new Reservation(trip, clientName, clientContact, numberOfReservedSeats);
        reservation.Id = id;
        return reservation;
    }
    
    
    public Reservation? FindOne(int id)
    {
        log.Info("Finding Reservation");

        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Reservation Id is null");
        }

        Reservation? reservation = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select " +
                                  "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                                  "r.clientName AS clientName, r.clientContact AS clientContact, " +
                                  "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                                  "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                                  "from reservation r " +
                                  "inner join trip t on t.id = r.tripId " +
                                  "where r.id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;

            command.Parameters.Add(parameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    reservation = GetReservationFromResult(dataReader);
                    log.InfoFormat("Exiting FindOne Reservation with value: " + reservation);
                    return reservation;
                }
            }
        }

        log.InfoFormat("Exiting FindOne Reservation with value: " + reservation);
        return reservation;
    }

    public IEnumerable<Reservation> FindAll()
    {
        log.Info("Finding All Reservations");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Reservation> reservations = new List<Reservation>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select " +
                                  "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                                  "r.clientName AS clientName, r.clientContact AS clientContact, " +
                                  "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                                  "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                                  "from reservation r " +
                                  "inner join trip t on t.id = r.tripId ";

            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Reservation reservation = GetReservationFromResult(dataReader);
                    reservations.Add(reservation);
                }
            }
        }

        log.InfoFormat("Exiting FindAll reservations with value: " + reservations);
        return reservations;
    }
    
    public Reservation? FindReservation(int tripId, string clientName, string clientContact, int numberOfReservedSeats)
    {
        log.Info("Finding Reservation by all");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (tripId == null || clientName == null || clientContact == null || numberOfReservedSeats == null || numberOfReservedSeats == 0)
        {
            throw new RepositoryException("Reservation tripId or clientName or clientContact or numberOfReservedSeats are null");
        }
        
        Reservation? reservation = null;
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select " +
                                  "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                                  "r.clientName AS clientName, r.clientContact AS clientContact, " +
                                  "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                                  "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                                  "from reservation r " +
                                  "inner join trip t on t.id = r.tripId " +
                                  "where r.tripId = @tripId and r.clientName = @clientName and r.clientContact = @clientContact and r.numberOfReservedSeats = @numberOfReservedSeats";
            IDbDataParameter tripParameter = command.CreateParameter();
            tripParameter.ParameterName = "@tripId";
            tripParameter.Value = tripId;
            command.Parameters.Add(tripParameter);
            
            IDbDataParameter clientNameParameter = command.CreateParameter();
            clientNameParameter.ParameterName = "@clientName";
            clientNameParameter.Value = clientName;
            command.Parameters.Add(clientNameParameter);
            
            IDbDataParameter clientContactParameter = command.CreateParameter();
            clientContactParameter.ParameterName = "@clientContact";
            clientContactParameter.Value = clientContact;
            command.Parameters.Add(clientContactParameter);
            
            IDbDataParameter numberOfReservedSeatsParameter = command.CreateParameter();
            numberOfReservedSeatsParameter.ParameterName = "@numberOfReservedSeats";
            numberOfReservedSeatsParameter.Value = numberOfReservedSeats;
            command.Parameters.Add(numberOfReservedSeatsParameter);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    reservation = GetReservationFromResult(dataReader);
                    log.InfoFormat("Exiting Find Reservation with value: " + reservation);
                    return reservation;
                }
            }
        }
        log.InfoFormat("Exiting Find Reservation  with value: " + reservation);
        return reservation;
    }

    
    public Reservation? Save(Reservation reservation)
    {
        log.Info("Saving Reservation");
        IDbConnection connection = DBUtils.getConnection(properties);

        _reservationValidator.Validate(reservation);

        Reservation? reservationFound = FindReservation(reservation.Trip.Id, reservation.ClientName, reservation.ClientContact, reservation.NumberOfReservedSeats);
        if (reservationFound != null)
        {
            log.InfoFormat("Reservation already exists with value: " + reservationFound);
            throw new RepositoryException("Reservation already exists");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText =
                "insert into reservation (tripId, clientName, clientContact, numberOfReservedSeats) values (@tripId, @clientName, @clientContact, @numberOfReservedSeats)";
            IDbDataParameter tripParameter = command.CreateParameter();
            tripParameter.ParameterName = "@tripId";
            tripParameter.Value = reservation.Trip.Id;
            command.Parameters.Add(tripParameter);
            
            IDbDataParameter clientNameParameter = command.CreateParameter();
            clientNameParameter.ParameterName = "@clientName";
            clientNameParameter.Value = reservation.ClientName;
            command.Parameters.Add(clientNameParameter);
            
            IDbDataParameter clientContactParameter = command.CreateParameter();
            clientContactParameter.ParameterName = "@clientContact";
            clientContactParameter.Value = reservation.ClientContact;
            command.Parameters.Add(clientContactParameter);
            
            IDbDataParameter numberOfReservedSeatsParameter = command.CreateParameter();
            numberOfReservedSeatsParameter.ParameterName = "@numberOfReservedSeats";
            numberOfReservedSeatsParameter.Value = reservation.NumberOfReservedSeats;
            command.Parameters.Add(numberOfReservedSeatsParameter);

            command.ExecuteNonQuery();

            Reservation? reservationF = FindReservation(reservation.Trip.Id, reservation.ClientName, reservation.ClientContact, reservation.NumberOfReservedSeats);
            reservation.Id = reservationF.Id;
            log.InfoFormat("Reservation saved with value: " + reservation);
        }

        return reservation;
    }

    public Reservation? Delete(int id)
    {
        log.Info("Deleting Reservation");
        IDbConnection connection = DBUtils.getConnection(properties);

        if (id == null)
        {
            throw new RepositoryException("Reservation Id is null");
        }
        
        Reservation? reservationFound = FindOne(id);
        if (reservationFound == null)
        {
            log.InfoFormat("Reservation is not found");
            throw new RepositoryException("Reservation is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "delete from reservation where id = @id";
            IDbDataParameter parameter = command.CreateParameter();
            parameter.ParameterName = "@id";
            parameter.Value = id;
            command.Parameters.Add(parameter);
        
            command.ExecuteNonQuery();

            log.InfoFormat("Reservation deleted with value: " + reservationFound);
        }

        return reservationFound;
    }

    public Reservation? Update(Reservation reservation)
    {
        log.Info("Updating Reservation");
        IDbConnection connection = DBUtils.getConnection(properties);

        _reservationValidator.Validate(reservation);

        Reservation? reservationFound = FindOne(reservation.Id);
        if (reservationFound == null)
        { 
            log.InfoFormat("Reservation is not found");
            throw new RepositoryException("Reservation is not found");
        }

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "update reservation set tripId = @tripId, numberOfReservedSeats = @numberOfReservedSeats where id = @id";
            IDbDataParameter tripParameter = command.CreateParameter();
            tripParameter.ParameterName = "@tripId";
            tripParameter.Value = reservation.Trip.Id;
            command.Parameters.Add(tripParameter);
            
            IDbDataParameter numberOfReservedSeatsParameter = command.CreateParameter();
            numberOfReservedSeatsParameter.ParameterName = "@numberOfReservedSeats";
            numberOfReservedSeatsParameter.Value = reservation.NumberOfReservedSeats;
            command.Parameters.Add(numberOfReservedSeatsParameter);
            
            IDbDataParameter idParameter = command.CreateParameter();
            idParameter.ParameterName = "@id";
            idParameter.Value = reservation.Id;
            command.Parameters.Add(idParameter);
            
            command.ExecuteNonQuery();
            
            log.InfoFormat("Agency added with value: " + reservation);
        }

        return reservation;
    }

    public IEnumerable<Reservation> FindReservationsByTrip(int tripId)
    {
        log.Info("Finding Reservations By Trip");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Reservation> reservations = new List<Reservation>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select " +
                                  "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                                  "r.clientName AS clientName, r.clientContact AS clientContact, " +
                                  "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                                  "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                                  "from reservation r " +
                                  "inner join trip t on t.id = r.tripId " +
                                  "where r.tripId = @tripId";
            IDbDataParameter tripIdParameter = command.CreateParameter();
            tripIdParameter.ParameterName = "@tripId";
            tripIdParameter.Value = tripId;
            command.Parameters.Add(tripIdParameter);
            
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Reservation reservation = GetReservationFromResult(dataReader);
                    reservations.Add(reservation);
                }
            }
        }

        log.InfoFormat("Exiting Find reservations by trip with value: " + reservations);
        return reservations;
    }
    
    public IEnumerable<Reservation> FindReservationsByClient(string clientName)
    {
        log.Info("Finding Reservations By Trip");
        IDbConnection connection = DBUtils.getConnection(properties);
        IList<Reservation> reservations = new List<Reservation>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "select " +
                                  "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                                  "r.clientName AS clientName, r.clientContact AS clientContact, " +
                                  "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                                  "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                                  "from reservation r " +
                                  "inner join trip t on t.id = r.tripId " +
                                  "where r.clientName = @clientName";
            IDbDataParameter clientNameParameter = command.CreateParameter();
            clientNameParameter.ParameterName = "@clientName";
            clientNameParameter.Value = clientName;
            command.Parameters.Add(clientNameParameter);
            
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Reservation reservation = GetReservationFromResult(dataReader);
                    reservations.Add(reservation);
                }
            }
        }

        log.InfoFormat("Exiting Find reservations by client with value: " + reservations);
        return reservations;
    }
}