package org.example.service;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.exception.RepositoryException;
import org.example.exception.ServiceException;
import org.example.modul.Agent;
import org.example.modul.Reservation;
import org.example.modul.Trip;
import org.example.repository.interfaces.AgentRepository;
import org.example.repository.interfaces.ReservationRepository;
import org.example.repository.interfaces.TripRepository;
import org.example.utils.event.ChangeEventType;
import org.example.utils.event.TravelAgencyEventType;
import org.example.utils.observer.Observable;
import org.example.utils.observer.Observer;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Service implements Observable<TravelAgencyEventType> {
    private static final Logger logger = LogManager.getLogger();

    private final AgentRepository agentRepository;
    private final ReservationRepository reservationRepository;
    private final TripRepository tripRepository;
    private List<Observer<TravelAgencyEventType>> observers = new ArrayList<>();


    public Service(AgentRepository agentRepository, ReservationRepository reservationRepository, TripRepository tripRepository) {
        this.agentRepository = agentRepository;
        this.reservationRepository = reservationRepository;
        this.tripRepository = tripRepository;
    }

    public Agent addAgent(Agent agent) {
        logger.traceEntry("Adding agent {}", agent);
        try {
            Agent result = agentRepository.save(agent).orElseThrow(() -> new ServiceException("Failed to save agent"));
            logger.traceExit(result);
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in addAgent: {}", e.getMessage());
            throw new ServiceException("Service error while adding agent", e);
        }
    }

    public Agent searchAgentByUsername(String username, String password){
        logger.traceEntry("Searching agent by username {}", username);
        try {
            Agent result = agentRepository.findByUsername(username, password).orElseThrow(() -> new ServiceException("Agent not found"));
            logger.traceExit(result);
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in searchAgentByUsername: {}", e.getMessage());
            throw new ServiceException("Service error while searching agent by username", e);
        }
    }

    public Trip updateSeatsOfTrip(Integer id, Integer seatsReserved) {
        logger.traceEntry("Updating seats of trip with id {}", id);
        try {
            Trip result = tripRepository.updateSeats(id, seatsReserved).orElseThrow(() -> new ServiceException("Failed to update seats of trip"));
            logger.traceExit(result);
            notifyObservers(new TravelAgencyEventType<>(ChangeEventType.RESERVEDSEAT, result));
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in updateSeatsOfTrip: {}", e.getMessage());
            throw new ServiceException("Service error while updating seats of trip", e);
        }
    }

    public Reservation addReservation(Reservation reservation) {
        logger.traceEntry("Adding reservation {}", reservation);
        try {
            Reservation result = reservationRepository.save(reservation).orElseThrow(() -> new ServiceException("Failed to save reservation"));
            Trip trip = updateSeatsOfTrip(reservation.getTrip().getId(), reservation.getNumberOfReservedSeats());
            logger.traceExit(result);
            notifyObservers(new TravelAgencyEventType<>(ChangeEventType.RESERVEDSEAT, result));
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in addReservation: {}", e.getMessage());
            throw new ServiceException("Service error while adding reservation", e);
        }
    }

    public Reservation deleteReservation(Integer id) {
        logger.traceEntry("Deleting reservation with id {}", id);
        try {
            Reservation reservation = reservationRepository.findOne(id).orElseThrow(() -> new ServiceException("Reservation not found"));
            Reservation result = reservationRepository.delete(id).orElseThrow(() -> new ServiceException("Failed to delete reservation"));
            logger.traceExit(result);
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in deleteReservation: {}", e.getMessage());
            throw new ServiceException("Service error while deleting reservation", e);
        }
    }

    public List<Trip> findAllTrips(){
        logger.traceEntry("Finding all trips");
        try {
            Iterable<Trip> result = tripRepository.findAll();
            logger.traceExit(result);
            List<Trip> trips = new ArrayList<Trip>();
            result.forEach(trips::add);
            return trips;
        } catch (RepositoryException e) {
            logger.error("Error in findAllTrips: {}", e.getMessage());
            throw new ServiceException("Service error while finding all trips", e);
        }
    }


    public Iterable<Trip> searchTrips(){
        logger.traceEntry("Searching trips");
        try {
            Iterable<Trip> result = tripRepository.findAll();
            logger.traceExit(result);
            if(result == null) {
                throw new ServiceException("No trips found");
            }
            return result;
        } catch (RepositoryException e) {
            logger.error("Error in searchTrips: {}", e.getMessage());
            throw new ServiceException("Service error while searching trips", e);
        }
    }

    public List<Trip> searchTripsByDestTime(String destination, LocalDate dataDeparture, LocalTime startTime, LocalTime endTime){
        logger.traceEntry("Searching trips by destination and time");
        try {
            Iterable<Trip> result = tripRepository.findTripsByDestination(destination);
            logger.traceExit(result);
            if(result == null) {
                throw new ServiceException("No trips found");
            }
            List<Trip> trips = new ArrayList<Trip>();
            result.forEach(trips::add);
            List<Trip> tripsByTime = new ArrayList<Trip>();
            for(Trip trip : trips) {
                LocalTime tripStartTime = trip.getDepartureDate().toLocalTime();
                LocalDate date = trip.getDepartureDate().toLocalDate();
                if((tripStartTime.isAfter(startTime) && tripStartTime.isBefore(endTime)) && date == dataDeparture) {
                    tripsByTime.add(trip);
                }
            }
            return trips;
        } catch (RepositoryException e) {
            logger.error("Error in searchTripsByDestTime: {}", e.getMessage());
            throw new ServiceException("Service error while searching trips by destination and time", e);
        }
    }

    public List<Reservation> findAllReservations(){
        logger.traceEntry("Finding all reservations");
        try {
            Iterable<Reservation> result = reservationRepository.findAll();
            logger.traceExit(result);
            List<Reservation> reservations = new ArrayList<Reservation>();
            result.forEach(reservations::add);
            return reservations;
        } catch (RepositoryException e) {
            logger.error("Error in findAllReservations: {}", e.getMessage());
            throw new ServiceException("Service error while finding all reservations", e);
        }
    }

    @Override
    public void addObserver(Observer<TravelAgencyEventType> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<TravelAgencyEventType> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(TravelAgencyEventType e) {
        observers.stream().forEach(x -> x.update(e));
    }
}
