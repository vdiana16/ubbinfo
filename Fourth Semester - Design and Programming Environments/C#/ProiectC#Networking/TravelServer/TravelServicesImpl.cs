using log4net;
using log4net.Core;
using TravelModel.model;
using TravelPersistence.persistence.interfaces;
using TravelPersistence.persistence.utils;
using TravelServices.services;

namespace TravelServer.server;

public class TravelServicesImpl : ITravelServices
{
    private IAgentRepository agentRepository;
    private ITourRepository _tourRepository;
    private IReservationRepository reservationRepository;
    
    private readonly IDictionary<string, ITravelObserver> loggedClients;
    private static readonly ILog logger = LogManager.GetLogger(typeof(TravelServicesImpl));

    public TravelServicesImpl(IAgentRepository agentRepository, ITourRepository tourRepository, IReservationRepository reservationRepository)
    {
        this.agentRepository = agentRepository;
        this._tourRepository = tourRepository;
        this.reservationRepository = reservationRepository;
        loggedClients = new Dictionary<string, ITravelObserver>();
    }

    public Agent login(string username, string password, ITravelObserver client)
    {
        var agent = agentRepository.FindByUsername(username, password);
        if (agent == null)
        {
            logger.Error("Login failed for user: " + username);
            throw new ServiceException("Authentication failed");
        }
        else
        {
            if (loggedClients.ContainsKey(username))
            {
                logger.Error("User already logged in: " + username);
                throw new ServiceException("User already logged in");
            }
            else
            {
                loggedClients[username] = client;
                logger.Info("User logged in: " + username);
                return agent;
            }
        }
    }

    public void logout(Agent agent)
    {
        loggedClients.Remove(agent.Username);
        logger.Info("User logged out: " + agent.Username);
    }

    public Agent AddAgent(Agent agent)
    {
        if (agent == null)
        {
            logger.Error("Agent is null");
            throw new ServiceException("Agent is null");
        }
        Agent agentSaved = agentRepository.Save(agent); 
        logger.Info("Agent added: " + agent.Username);
        return agentSaved;
    }

    private Tour updateSeatsOfTour(int tourId, int numberOfReservedSeats)
    {
        Tour tour = _tourRepository.UpdateSeats(tourId, numberOfReservedSeats);
        return tour;
    }
    
    
    public Reservation AddReservation(Reservation reservation)
    {
        if (reservation == null)
        {
            logger.Error("Reservation is null");
            throw new ServiceException("Reservation is null");
        }
        Reservation reservationSaved = reservationRepository.Save(reservation);
        Tour tourFound = _tourRepository.FindOne(reservation.Tour.Id);
        if (tourFound.NumberOfAvailableSeats < reservation.NumberOfReservedSeats)
        {
            logger.Error("Not enough available seats for tour: " + tourFound.Id);
            throw new ServiceException("Not enough available seats");
        }
        Tour tour = updateSeatsOfTour(reservation.Tour.Id, reservationSaved.NumberOfReservedSeats);
        notifyLoggedClients(tour);   
        return reservation;
    }

    private void notifyLoggedClients(Tour tour)
    {
        foreach (var client in loggedClients)
        {
            ITravelObserver clientObserver = client.Value;
            Task.Run(()=>clientObserver.tourModified(tour));
        }
    }

    public IEnumerable<Tour> GetAllTours()
    {
        logger.Info("Getting all tours");
        try
        {
            IEnumerable<Tour> result = _tourRepository.FindAll() ?? throw new ServiceException("Failed to get all tours");
            logger.Info("Tours retrieved successfully " + result);
            List<Tour> tours = result.ToList();
            return tours;
        }
        catch (RepositoryException e)
        {
            logger.Error("Failed to get all tours", e);
            throw new ServiceException("Failed to get all tours", e);
        }
    }
    
    public IEnumerable<Reservation> GetAllReservations()
    {
        logger.Info("Getting all reservations");
        try
        {
            IEnumerable<Reservation> result = reservationRepository.FindAll() ?? throw new ServiceException("Failed to get all reservations");
            logger.Info("Reservations retrieved successfully " + result);
            List<Reservation> reservations = result.ToList();
            return reservations;
        }
        catch (RepositoryException e)
        {
            logger.Error("Failed to get all reservations", e);
            throw new ServiceException("Failed to get all reservations", e);
        }
    }
    
    public IEnumerable<Tour> GetToursByDestination(string destination, DateTime departureDate, TimeSpan startTime, TimeSpan endTime)
    {
        try
        {
            IEnumerable<Tour> result = _tourRepository.FindToursByDestination(destination) ?? throw new ServiceException("Failed to search tours by destination");
            logger.Info("Tours found " + result);
            List<Tour> tours = result.ToList();
            tours = tours.Where(t => t.DepartureDate.Date == departureDate.Date &&
                                     t.DepartureDate.TimeOfDay >= startTime &&
                                     t.DepartureDate.TimeOfDay <= endTime).ToList();
            return tours;
        }
        catch (RepositoryException e)
        {
            logger.Error("Failed to search tours by destination " + destination, e);
            throw new ServiceException("Failed to search tours by destination", e);
        }
    }
    
    public Tour GetTourById(int id)
    {
        logger.Info("Getting tour by id " + id);
        try
        {
            Tour result = _tourRepository.FindOne(id) ?? throw new ServiceException("Failed to get tour by id");
            logger.Info("Tour retrieved successfully " + result);
            return result;
        }
        catch (RepositoryException e)
        {
            logger.Error("Failed to get tour by id " + id, e);
            throw new ServiceException("Failed to get tour by id", e);
        }
    }

    public void logoutForSignUp()
    {
        loggedClients.Clear();
        logger.Info("All users logged out");
    }
}