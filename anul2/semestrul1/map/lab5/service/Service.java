package org.example.service;


/**
 * Interface for generic entities
 * @param <E> the type of entity managed by the service
 */

public interface Service<E> {
    /**
     * Generates a unique ID for an entity
     * @return the ID
     */
    Long generateID();
}
