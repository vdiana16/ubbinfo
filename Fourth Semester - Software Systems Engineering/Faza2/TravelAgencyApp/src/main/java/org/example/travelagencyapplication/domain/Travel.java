package org.example.travelagencyapplication.domain;

import jakarta.persistence.Entity;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import jakarta.persistence.Table;

import java.time.LocalDateTime;

@Entity
@Table(name = "travels")
public class Travel extends Identifiable<Integer> {
    private String destination;
    private LocalDateTime departureDate;
    private String transportCompany;
    private Integer numberOfAvailableSeats;
    private Double price;

    public Travel() {
    }

    public Travel(String destination, LocalDateTime departureDate, String transportCompany, Integer numberOfAvailableSeats, Double price) {
        this.destination = destination;
        this.departureDate = departureDate;
        this.transportCompany = transportCompany;
        this.numberOfAvailableSeats = numberOfAvailableSeats;
        this.price = price;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public LocalDateTime getDepartureDate() {
        return departureDate;
    }

    public void setDepartureDate(LocalDateTime departureDate) {
        this.departureDate = departureDate;
    }

    public String getTransportCompany() {
        return transportCompany;
    }

    public void setTransportCompany(String transportCompany) {
        this.transportCompany = transportCompany;
    }

    public Integer getNumberOfAvailableSeats() {
        return numberOfAvailableSeats;
    }

    public void setNumberOfAvailableSeats(Integer numberOfAvailableSeats) {
        this.numberOfAvailableSeats = numberOfAvailableSeats;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }
}
