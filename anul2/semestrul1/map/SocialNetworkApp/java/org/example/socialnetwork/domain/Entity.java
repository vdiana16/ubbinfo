package org.example.socialnetwork.domain;

/**
 * Abstract class for an entity
 * @param <ID> - type of the id for entity
 */

public class Entity<ID> {
    //The id of the entity
    private ID id;

    /**
     * Getter for entity
     * @return id - the id of the entity
     */
    public ID getId() {
        return id;
    }


    /**
     * Setter for entity
     * @param id - the new id
     */
    public void setId(ID id) {
        this.id = id;
    }
}