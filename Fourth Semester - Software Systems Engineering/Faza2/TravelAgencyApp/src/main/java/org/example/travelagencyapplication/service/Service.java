package org.example.travelagencyapplication.service;
import org.example.travelagencyapplication.domain.Status;
import org.example.travelagencyapplication.domain.Travel;
import org.example.travelagencyapplication.domain.User;
import org.example.travelagencyapplication.repository.ReservationRepository;
import org.example.travelagencyapplication.repository.TravelRepository;
import org.example.travelagencyapplication.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.example.travelagencyapplication.service.ServiceException;

import java.time.LocalDateTime;
import java.util.List;

@org.springframework.stereotype.Service
public class Service {
    private UserRepository userRepository;
    private TravelRepository travelRepository;
    private ReservationRepository reservationRepository;

    public Service() {
    }

    @Autowired
    public void setUserRepository(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Autowired
    public void setTravelRepository(TravelRepository travelRepository) {
        this.travelRepository = travelRepository;
    }

    @Autowired
    public void setReservationRepository(ReservationRepository reservationRepository) {
        this.reservationRepository = reservationRepository;
    }

    public Travel addTravel(String destination, LocalDateTime departureDate, String transportCompany, Integer numberOfAvailableSeats, Double price) {
        Travel travel = new Travel(destination, departureDate, transportCompany, numberOfAvailableSeats, price);
        Travel travelSaved = travelRepository.save(travel);
        return travelSaved;
    }

    public User addUser(String name, String username, String password, String agencyName, Status status) {
        User user = new User(name, username, password, agencyName, status);
        User userSaved = userRepository.save(user);
        return userSaved;
    }

    public List<Travel> findAllTravels() {
        return travelRepository.findAll();
    }

    public User login(String username, String password) {
        User userFound = userRepository.findByUsernameAndPassword(username, password);
        if (userFound != null) {
            return userFound;
        } else {
            throw new ServiceException("Invalid username or password");
        }
    }
}
