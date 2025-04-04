package org.example.utils.observer;

import org.example.utils.event.Event;

public interface Observer <E extends Event> {
    void update(E event);
}