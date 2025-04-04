using log4net;
using TravelAgency.exception;
using TravelAgency.model;
using TravelAgency.repository;
using TravelAgency.utils;

namespace TravelAgency.service;

public class Service 
{
    private static readonly ILog log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
    
    private IAgentRepository _agentRepository;
    private IReservationRepository reservationRepository;
    private ITripRepository tripRepository;
    
    public Service(IAgentRepository agentRepository,
        IReservationRepository reservationRepository, ITripRepository tripRepository)
    {
        log.Info("Creating Service");
        this._agentRepository = agentRepository;
        this.reservationRepository = reservationRepository;
        this.tripRepository = tripRepository;
    }

    public Agent AddAgent(Agent agent)
    {
        log.Info("Adding agent " + agent);
        try
        {
            Agent result = _agentRepository.Save(agent) ?? throw new ServiceException("Failed to save agent");
            log.Info("Agent added successfully " + agent);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to add agent " + agent, e);
            throw new ServiceException("Failed to add agent", e);
        }
    }

    public Agent SearchAgentByUsername(string username, string password)
    {
        log.Info("Searching agent by username " + username);
        try
        {
            Agent result = _agentRepository.FindByUsername(username, password) ??
                           throw new ServiceException("Failed to find agent by username");
            log.Info("Agent found " + result);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to search agent by username " + username, e);
            throw new ServiceException("Failed to search agent", e);
        }
    }

    public Trip UpdateSeatsOfTrip(int id, int seatsReserved)
    {
        log.Info("Updating seats of trip " + id);
        try
        {
            Trip result = tripRepository.UpdateSeats(id, seatsReserved) ?? throw new ServiceException("Failed to update trip");
            log.Info("Trip updated successfully " + result);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to update seats of trip " + id, e);
            throw new ServiceException("Failed to update seats of trip", e);
        }
    }

    public Reservation AddReservation(Reservation reservation)
    {
        log.Info("Adding reservation " + reservation);
        try
        {
            Reservation result = reservationRepository.Save(reservation) ?? throw new ServiceException("Failed to save reservation");
            Trip trip = UpdateSeatsOfTrip(reservation.Trip.Id, reservation.NumberOfReservedSeats);
            log.Info("Reservation added successfully " + reservation);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to add reservation " + reservation, e);
            throw new ServiceException("Failed to add reservation", e);
        }
    }

    public Reservation DeleteReservation(int id)
    {
        log.Info("Deleting reservation " + id);
        try
        {
            Reservation result = reservationRepository.Delete(id) ?? throw new ServiceException("Failed to delete reservation");
            Trip trip = UpdateSeatsOfTrip(result.Trip.Id, -result.NumberOfReservedSeats);
            log.Info("Reservation deleted successfully " + result);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to delete reservation " + id, e);
            throw new ServiceException("Failed to delete reservation", e);
        }
    }
    
    public List<Trip> GetAllTrips()
    {
        log.Info("Getting all trips");
        try
        {
            IEnumerable<Trip> result = tripRepository.FindAll() ?? throw new ServiceException("Failed to get all trips");
            log.Info("Trips retrieved successfully " + result);
            List<Trip> trips = result.ToList();
            return trips;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to get all trips", e);
            throw new ServiceException("Failed to get all trips", e);
        }
    }

    public List<Trip> SearchTripsByDestTime(string destination, DateTime departureDate, TimeSpan startTime,
        TimeSpan endTime)
    {
        log.Info("Searching trips by destination " + destination);
        try
        {
            IEnumerable<Trip> result = tripRepository.FindTripsByDestination(destination) ?? throw new ServiceException("Failed to search trips by destination");
            log.Info("Trips found " + result);
            List<Trip> trips = result.ToList();
            trips = trips.Where(t => t.DepartureDate.Date == departureDate.Date &&
                                     t.DepartureDate.TimeOfDay >= startTime &&
                                     t.DepartureDate.TimeOfDay <= endTime).ToList();
            return trips;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to search trips by destination " + destination, e);
            throw new ServiceException("Failed to search trips by destination", e);
        }
    }
    
    public List<Reservation> GetAllReservations()
    {
        log.Info("Getting all reservations");
        try
        {
            IEnumerable<Reservation> result = reservationRepository.FindAll() ?? throw new ServiceException("Failed to get all reservations");
            log.Info("Reservations retrieved successfully " + result);
            List<Reservation> reservations = result.ToList();
            return reservations;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to get all reservations", e);
            throw new ServiceException("Failed to get all reservations", e);
        }
    }
    
    public Trip GetTripById(int id)
    {
        log.Info("Getting trip by id " + id);
        try
        {
            Trip result = tripRepository.FindOne(id) ?? throw new ServiceException("Failed to get trip by id");
            log.Info("Trip retrieved successfully " + result);
            return result;
        }
        catch (RepositoryException e)
        {
            log.Error("Failed to get trip by id " + id, e);
            throw new ServiceException("Failed to get trip by id", e);
        }
    }
}