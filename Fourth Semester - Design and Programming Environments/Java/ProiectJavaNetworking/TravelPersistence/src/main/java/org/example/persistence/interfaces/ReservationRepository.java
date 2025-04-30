package org.example.persistence.interfaces;


import org.example.model.Reservation;
import org.example.persistence.Repository;

import java.util.Optional;

public interface ReservationRepository extends Repository<Integer, Reservation> {
    Optional<Reservation> findReservation(Integer tripId, String nameClient, String contactClient, Integer numberOfReservedSeats);
    Iterable<Reservation> findReservationsByTour(Integer tourId);
    Iterable<Reservation> findReservationsByClient(String clientName);
}
