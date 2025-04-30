package org.example.model.validator;


import org.example.model.Reservation;

public class ReservationValidator implements Validator<Reservation> {
    @Override
    public void validate(Reservation entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Agency is null");
        }
        if (entity.getNumberOfReservedSeats() == null) {
            throw new ValidationException("Number of reserved places is null");
        }
        if (entity.getTour() == null) {
            throw new ValidationException("Tour is null");
        }
    }
}
