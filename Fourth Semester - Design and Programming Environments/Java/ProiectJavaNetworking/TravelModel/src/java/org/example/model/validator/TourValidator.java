package org.example.model.validator;

import org.example.model.Tour;

public class TourValidator implements Validator<Tour> {
    @Override
    public void validate(Tour entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Tour is null");
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