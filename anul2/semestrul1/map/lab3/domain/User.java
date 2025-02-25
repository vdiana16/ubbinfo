
package domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * Class representing a User
 */
public class User extends Entity<Long> {
    private String firstName;           //the user's first name
    private String lastName;            //the user's last name

    /**
     * Constructor for creating a user object.
     * @param firstName  the user's first name
     * @param lastName  the user's last name
     */
    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
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
     * Returns a string representation of the User.
     * @return A string describing the user.
     */
    @Override
    public String toString() {
        return "User{" +
                "'firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' + "}";
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
        if (o == null || getClass() != o.getClass()) return false;
        User that = (User) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());
    }

    /**
     * Generates a hash code for the User.
     * @return friends - The hash code of the User.
     */
    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
    }
}
