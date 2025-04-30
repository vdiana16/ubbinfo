package org.example.model;

import java.util.Objects;

public class Reservation extends Entity<Integer> {
    private Tour tour;
    private String clientName;
    private String clientContact;
    private Integer numberOfReservedSeats;

    public Reservation(Tour tour, String clientName, String clientContact, Integer numberOfReservedSeats) {
        this.tour = tour;
        this.clientName = clientName;
        this.clientContact = clientContact;
        this.numberOfReservedSeats = numberOfReservedSeats;
    }

    public Tour getTour() {
        return tour;
    }

    public void setTour(Tour tour) {
        this.tour = tour;
    }

    public String getClientName() {
        return clientName;
    }

    public void setClientName(String clientName) {
        this.clientName = clientName;
    }

    public String getClientContact() {
        return clientContact;
    }

    public void setClientContact(String clientContact) {
        this.clientContact = clientContact;
    }

    public Integer getNumberOfReservedSeats() {
        return numberOfReservedSeats;
    }

    public void setNumberOfReservedSeats(Integer numberOfReservedSeats) { this.numberOfReservedSeats = numberOfReservedSeats; }


    @Override
    public String toString() {
        return "Reservation{" +
                "tour=" + tour +
                ", nameClient='" + clientName +
                ", contactClient='" + clientContact +
                ", numberOfReservedPlaces=" + numberOfReservedSeats +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if(!(obj instanceof Reservation reservation)) {
            return false;
        }
        return getTour().equals(reservation.getTour()) && getClientName().equals(reservation.getClientName()) &&
                getClientContact().equals(reservation.getClientContact()) &&
                getNumberOfReservedSeats().equals(reservation.getNumberOfReservedSeats());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTour(), getClientName(), getClientContact(), getNumberOfReservedSeats());
    }
}
