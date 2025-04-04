package org.example.socialnetwork.utils.observer;


import org.example.socialnetwork.utils.events.Event;

public interface Observer <E extends Event> {
    void update(E event);
}
