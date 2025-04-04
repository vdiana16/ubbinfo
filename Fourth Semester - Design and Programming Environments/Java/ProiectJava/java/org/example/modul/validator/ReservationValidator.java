package org.example.modul.validator;


import org.example.exception.ValidationException;
import org.example.modul.Reservation;

public class ReservationValidator implements Validator<Reservation> {
    @Override
    public void validate(Reservation entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Agency is null");
        }
        if (entity.getNumberOfReservedSeats() == null) {
            throw new ValidationException("Number of reserved places is null");
        }
        if (entity.getTrip() == null) {
            throw new ValidationException("Travel is null");
        }
    }
}
