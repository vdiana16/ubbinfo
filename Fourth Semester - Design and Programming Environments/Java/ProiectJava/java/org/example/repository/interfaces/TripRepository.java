package org.example.repository.interfaces;

import org.example.modul.Trip;
import org.example.repository.Repository;

import java.time.LocalDateTime;
import java.util.Optional;

public interface TripRepository extends Repository<Integer, Trip> {
    Optional<Trip> updateSeats(Integer id, Integer numberOfReservedSeats);
    Optional<Trip> findTrip(String destination, String transportCompany, LocalDateTime departureDate, Double price, Integer numberOfAvailableSeats);
    Iterable<Trip> findTripsByDestination(String destination);
}
