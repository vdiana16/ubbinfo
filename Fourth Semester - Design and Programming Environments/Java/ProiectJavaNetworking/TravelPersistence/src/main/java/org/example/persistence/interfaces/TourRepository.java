package org.example.persistence.interfaces;

import org.example.model.Tour;
import org.example.persistence.Repository;

import java.time.LocalDateTime;
import java.util.Optional;

public interface TourRepository extends Repository<Integer, Tour> {
    Optional<Tour> updateSeats(Integer id, Integer numberOfReservedSeats);
    Optional<Tour> findTour(String destination, String transportCompany, LocalDateTime departureDate, Double price, Integer numberOfAvailableSeats);
    Iterable<Tour> findToursByDestination(String destination);
}
