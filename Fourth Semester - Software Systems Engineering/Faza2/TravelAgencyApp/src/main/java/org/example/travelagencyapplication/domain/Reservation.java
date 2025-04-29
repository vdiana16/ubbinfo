package org.example.travelagencyapplication.domain;

import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

@Entity
@Table(name="reservations")
public class Reservation extends Identifiable<Integer>{
    private String clientName;
    private Integer numberOfReservedSeats;

    @ManyToOne
    @JoinColumn(name = "travel_id")
    private Travel travel;

    public Travel getTravel() {
        return travel;
    }

    public void setTravel(Travel travel) {
        this.travel = travel;
    }

    public Reservation() {
    }

    public Reservation(String clientName, Integer numberOfReservedSeats, Travel travel) {
        this.clientName = clientName;
        this.numberOfReservedSeats = numberOfReservedSeats;
        this.travel = travel;
    }

    public String getClientName() {
        return clientName;
    }

    public void setClientName(String clientName) {
        this.clientName = clientName;
    }

    public Integer getNumberOfReservedSeats() {
        return numberOfReservedSeats;
    }

    public void setNumberOfReservedSeats(Integer numberOfReservedSeats) {
        this.numberOfReservedSeats = numberOfReservedSeats;
    }
}
