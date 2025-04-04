package org.example.utils.observer;

import org.example.utils.event.Event;

public interface Observable <E extends Event> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E e);
}