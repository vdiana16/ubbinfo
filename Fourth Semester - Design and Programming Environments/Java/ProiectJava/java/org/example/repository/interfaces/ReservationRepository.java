package org.example.repository.interfaces;

import org.example.modul.Reservation;
import org.example.repository.Repository;

import java.util.Optional;

public interface ReservationRepository extends Repository<Integer, Reservation> {
    Optional<Reservation> findReservation(Integer tripId, String nameClient, String contactClient, Integer numberOfReservedSeats);
    Iterable<Reservation> findReservationsByTrip(Integer tripId);
    Iterable<Reservation> findReservationsByClient(String clientName);
}
