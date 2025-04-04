package org.example.modul;

import java.util.Objects;

public class Reservation extends Entity<Integer> {
    private Trip travel;
    private String clientName;
    private String clientContact;
    private Integer numberOfReservedSeats;

    public Reservation(Trip travel, String clientName, String clientContact, Integer numberOfReservedSeats) {
        this.travel = travel;
        this.clientName = clientName;
        this.clientContact = clientContact;
        this.numberOfReservedSeats = numberOfReservedSeats;
    }

    public Trip getTrip() {
        return travel;
    }

    public void setTrip(Trip travel) {
        this.travel = travel;
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
                "travel=" + travel +
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
        return getTrip().equals(reservation.getTrip()) && getClientName().equals(reservation.getClientName()) &&
                getClientContact().equals(reservation.getClientContact()) &&
                getNumberOfReservedSeats().equals(reservation.getNumberOfReservedSeats());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTrip(), getClientName(), getClientContact(), getNumberOfReservedSeats());
    }
}
