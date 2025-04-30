package org.example.services;

import org.example.model.Tour;

public interface TravelObserver {
    void tourModified(Tour tour) throws ServiceException;
}
