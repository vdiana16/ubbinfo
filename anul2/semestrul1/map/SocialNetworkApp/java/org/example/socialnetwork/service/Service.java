package org.example.socialnetwork.service;

import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.User;

import java.util.ArrayList;

/**
 * Interface for a service that manages users and friendships.
 * @param <ID> the type of the identifier for users and friendships
 */

public interface Service<ID> {
    /**
     * Adds a new user to the system.
     * @param firstName
     * @param lastName
     * @return true if the user was succesfully added
     *          false, otherwise
     */
    boolean addUser(String firstName, String lastName, String username, String password);

    /**
     * Removes a user from the system based on the user's id
     * @param id - the id of the user to be removed
     * @return the removed User object, or null if no user was found with the given id
     */
    User removeUser(ID id);

    /**
     * Add a friendships between two users identified by their ids.
     * @param id1 - the id of the first user
     * @param id2 - the id of the second user
     * @return true if the friendship was successfully added
     *          false, otherwise
     */
    boolean addFriendship(ID id1, ID id2);

    /**
     * Removes a friendship between two users identifies by their ids.
     * @param id1 - the id of the first user
     * @param id2 - the id of the second user
     * @return true if the friendship was successfully removed
     *      *          false, otherwise
     */
    boolean removeFriendship(ID id1, ID id2);

    /**
     * Retrieves all users in the system.
     * @return an iterable collection of all User objects
     */
    Iterable<User> getAllUsers();

    /**
     * Retrieves all friendships in the system.
     * @return an iterable collection of all Friendship objects
     */
    Iterable<Friendship> getAllFriendships();

    /**
     * Calculates the number of distinct communities
     * @return the number of distinct communities
     */
    int numberOfCommunities();

    /**
     * Retrieves the most sociable community
     * @return an ArrayList of User objects representing the most sociable community
     */
    ArrayList<User> getMostSociableCommunity();
}