package org.example.modul;

import java.time.LocalDateTime;

public class Trip extends Entity<Integer> {
    private String destination;
    private String transportCompany;
    private LocalDateTime departureDate;
    private Double price;
    private Integer numberOfAvailableSeats;

    public Trip(String destination, String transportCompany, LocalDateTime departureDate, Double price, Integer numberOfAvailableSeats) {
        this.destination = destination;
        this.transportCompany = transportCompany;
        this.departureDate = departureDate;
        this.price = price;
        this.numberOfAvailableSeats = numberOfAvailableSeats;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public String getTransportCompany() {
        return transportCompany;
    }

    public void setTransportCompany(String transportCompany) {
        this.transportCompany = transportCompany;
    }

    public LocalDateTime getDepartureDate() {
        return departureDate;
    }

    public void setDepartureDate(LocalDateTime departureDate) {
        this.departureDate = departureDate;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public Integer getNumberOfAvailableSeats() {
        return numberOfAvailableSeats;
    }

    public void setNumberOfAvailableSeats(Integer numberOfAvailableSeats) {
        this.numberOfAvailableSeats = numberOfAvailableSeats;
    }

    @Override
    public String toString() {
        return "Travel{" +
                "id=" + getId() +
                ", destination='" + destination + '\'' +
                ", transportCompany='" + transportCompany + '\'' +
                ", departureDate=" + departureDate +
                ", price=" + price +
                ", numberOfAvailablePlaces=" + numberOfAvailableSeats +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if(!(obj instanceof Trip trip)) {
            return false;
        }
        return getDestination().equals(trip.getDestination()) && getTransportCompany().equals(trip.getTransportCompany()) && getDepartureDate().equals(trip.getDepartureDate()) && getPrice().equals(trip.getPrice()) && getNumberOfAvailableSeats().equals(trip.getNumberOfAvailableSeats());
    }

    @Override
    public int hashCode() {
        return 31 * (getDestination().hashCode() + getTransportCompany().hashCode() + getDepartureDate().hashCode() + getPrice().hashCode() + getNumberOfAvailableSeats().hashCode());
    }
}
