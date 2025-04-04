package org.example.socialnetwork.domain;

import java.util.ArrayList;
import java.util.Objects;

/**
 * Class representing a User
 */
public class User extends Entity<Long> {
    private String firstName;           //the user's first name
    private String lastName;            //the user's last name
    private String username;
    private String password;

    /**
     * Constructor for creating a user object.
     * @param firstName  the user's first name
     * @param lastName  the user's last name
     */
    public User(String firstName, String lastName, String username, String password) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.username = username;
        this.password = password;
    }

    /**
     * Getter for the user's firstName.
     * @return firstName
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Setter for the user's firstName.
     * @param firstName - The firstName to set.
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Getter for the user's lastName.
     * @return lastName
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Setter for the user's lastName.
     * @param lastName - The lastName to set.
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * Getter for the user's username
     * @return username
     */
    public String getUsername() {
        return username;
    }

    /**
     * Setter for the user's username
     * @param username
     */
    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Returns a string representation of the User.
     * @return A string describing the user.
     */
    @Override
    public String toString() {
        return "User{" +
                "'firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' + ", " +
                "username='" + username + '\'' + "}";
    }

    /**
     * Checks if two Users objects are equal, based on thei atributes.
     * @param o - The object to compare with.
     * @return true,  if the objects are considered equal,
     *          false, otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if(!(o instanceof User)) return false;
        return getUsername().equals(((User) o).getUsername());
    }

    /**
     * Generates a hash code for the User.
     * @return friends - The hash code of the User.
     */
    @Override
    public int hashCode() {
        return Objects.hash(getUsername());
    }
}