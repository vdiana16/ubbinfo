package org.example.socialnetwork.utils.events;

import org.example.socialnetwork.domain.Entity;

public class SocialNetworkChangeEvent<E extends Entity> implements Event {
    private ChangeEventType type;
    private E data, oldata;

    public SocialNetworkChangeEvent(ChangeEventType type, E data) {
        this.type = type;
        this.data = data;
    }

    public SocialNetworkChangeEvent(ChangeEventType type, E data, E oldata) {
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
