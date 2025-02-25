package org.example.socialnetwork.utils.observer;


import org.example.socialnetwork.utils.events.Event;

public interface Observable <E extends Event> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E e);
}
