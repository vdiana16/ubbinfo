package org.example.server;

import org.example.model.Agent;
import org.example.model.Reservation;
import org.example.model.Tour;
import org.example.persistence.interfaces.AgentRepository;
import org.example.persistence.interfaces.ReservationRepository;
import org.example.persistence.interfaces.TourRepository;
import org.example.services.ServiceException;
import org.example.services.TravelObserver;
import org.example.services.TravelServices;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class TravelServicesImpl implements TravelServices {
    private AgentRepository agentRepository;
    private TourRepository tourRepository;
    private ReservationRepository reservationRepository;

    private Map<String, TravelObserver> loggedAgents;

    public TravelServicesImpl(AgentRepository agentRepository, TourRepository tourRepository, ReservationRepository reservationRepository) {
        this.agentRepository = agentRepository;
        this.tourRepository = tourRepository;
        this.reservationRepository = reservationRepository;
        loggedAgents = new ConcurrentHashMap<>();
    }

    @Override
    public synchronized Agent login(String username, String password, TravelObserver client) throws ServiceException {
        Optional<Agent> agentFound = agentRepository.findByUsername(username, password);
        if (agentFound.isPresent()){
            if (loggedAgents.get(username) != null) {
                throw new ServiceException("Agent already logged in!");
            }
            loggedAgents.put(username, client);
            return agentFound.get();
        } else {
            throw new ServiceException("Authentication failed!");
        }
    }

    @Override
    public synchronized Tour[] getAllTours() throws ServiceException {
        Iterable<Tour> tours = tourRepository.findAll();
        if (tours == null) {
            throw new ServiceException("No tours found!");
        }
        Set<Tour> result = new TreeSet<>(Comparator.comparing(Tour::getId));
        tours.forEach(result::add);
        return result.toArray(new Tour[result.size()]);
    }

    @Override
    public synchronized Reservation[] getAllReservations() throws ServiceException {
        Iterable<Reservation> reservations = reservationRepository.findAll();
        if (reservations == null) {
            throw new ServiceException("No reservations found!");
        }
        Set<Reservation> result = new TreeSet<>(Comparator.comparing(Reservation::getId));
        reservations.forEach(result::add);
        return result.toArray(new Reservation[result.size()]);
    }

    @Override
    public synchronized List<Tour> getToursByDestination(String destination, LocalDate departureDate, LocalTime startTime, LocalTime endTime) throws ServiceException {
        Iterable<Tour> tours = tourRepository.findToursByDestination(destination);
        if (tours == null) {
            throw new ServiceException("No tours found for the given destination!");
        }
        List<Tour> filteredTours = new ArrayList<>();
        for (Tour tour : tours) {
            LocalDate tourDate = tour.getDepartureDate().toLocalDate();
            LocalTime tourTime = tour.getDepartureDate().toLocalTime();
            if (tourDate.equals(departureDate) && (tourTime.isAfter(startTime) && tourTime.isBefore(endTime))) {
                filteredTours.add(tour);
            }
        }
        return filteredTours;
    }

    public Tour updateSeatsOfTour(Integer id, Integer seatsReserved) {
        Tour result = tourRepository.updateSeats(id, seatsReserved).orElse(null);
        return result;
    }

    @Override
    public synchronized void addReservation(Reservation reservation) throws ServiceException {
        if (reservation == null) {
            throw new ServiceException("Reservation cannot be null!");
        }
        Reservation reservationSaved = reservationRepository.save(reservation).orElseThrow(() -> new ServiceException("Error saving reservation!"));
        Tour tour = updateSeatsOfTour(reservationSaved.getTour().getId(), reservationSaved.getNumberOfReservedSeats());
        for (TravelObserver observer : loggedAgents.values()) {
            try {
                observer.tourModified(tour);
            } catch (ServiceException e) {
                System.out.println("Error notifying agent: " + e.getMessage());
            }
        }
    }

    @Override
    public synchronized Agent addAgent(Agent agent) throws ServiceException {
        if (agent == null) {
            throw new ServiceException("Agent cannot be null!");
        }
        Agent agentSaved = agentRepository.save(agent).orElse(null);
        return agentSaved;
    }

    @Override
    public synchronized void logout(Agent agent, TravelObserver client) throws ServiceException {
        TravelObserver localClient = loggedAgents.remove(agent.getUsername());
        if (localClient == null) {
            throw new ServiceException("Agent " + agent.getUsername() + " is not logged in.");
        }
        System.out.println("Agent " + agent.getUsername() + " logged out.");
    }

    @Override
    public synchronized void logoutForSignUp(Agent agent) throws ServiceException {
        System.out.println("All agents logged out.");
    }
}
