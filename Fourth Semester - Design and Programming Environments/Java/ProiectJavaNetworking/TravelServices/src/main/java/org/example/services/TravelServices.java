package org.example.services;



import org.example.model.Agent;
import org.example.model.Reservation;
import org.example.model.Tour;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.List;

public interface TravelServices {
    Agent login(String username, String password, TravelObserver client) throws ServiceException;

    Tour[] getAllTours() throws ServiceException;

    Reservation[] getAllReservations() throws ServiceException;

    List<Tour> getToursByDestination(String destination, LocalDate departureDate, LocalTime startTime, LocalTime endTime) throws ServiceException;

    Agent addAgent(Agent agent) throws ServiceException;

    void addReservation(Reservation reservation) throws ServiceException;

    void logout(Agent agent, TravelObserver client) throws ServiceException;

    void logoutForSignUp(Agent agent) throws ServiceException;
}
