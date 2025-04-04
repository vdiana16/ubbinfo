package org.example.utils.event;

import org.example.modul.Entity;

public class TravelAgencyEventType <E extends Entity> implements Event {
    private ChangeEventType type;
    private E data, oldata;

    public TravelAgencyEventType(ChangeEventType type, E data) {
        this.type = type;
        this.data = data;
    }

    public TravelAgencyEventType(ChangeEventType type, E data, E oldata) {
        this.type = type;
        this.data = data;
        this.oldata = oldata;
    }

    public ChangeEventType getType() {
        return type;
    }

    public E getOldata() {
        return oldata;
    }

    public E getData() {
        return data;
    }
}