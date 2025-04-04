package org.example.modul.validator;


import org.example.exception.ValidationException;
import org.example.modul.Trip;

public class TripValidator implements Validator<Trip> {
    @Override
    public void validate(Trip entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Trip is null");
        }
        if (entity.getDestination() == null || entity.getDestination().isEmpty()) {
            throw new ValidationException("Destination is empty");
        }
        if (entity.getDepartureDate() == null) {
            throw new ValidationException("Departure date is null");
        }
        if (entity.getNumberOfAvailableSeats() == null) {
            throw new ValidationException("Number of available places is null");
        }
        if (entity.getPrice() < 0) {
            throw new ValidationException("Price is negative");
        }
    }
}