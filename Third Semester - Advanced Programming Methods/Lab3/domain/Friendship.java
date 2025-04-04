package domain;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

/**
 * Class representing a Friendship between two users.
 */
public class Friendship extends Entity<Long> {
    private final User user1;     //The first user.
    private final User user2;     //The second user.

    /**
     * Constructor for creating a Friendship object.
     * @param user1 - The first user
     * @param user2 - The second user
     */
    public Friendship(User user1, User user2) {
        this.user1 = user1;
        this.user2 = user2;
    }

    /**
     * Getter for the first user
     * @return: user1
     */
    public User getUser1() {
        return user1;
    }

    /**
     * Getter for the second user
     * @return: user2
     */
    public User getUser2() {
        return user2;
    }

    /**
     * Setter for the first user
     * @param user1 - first user
     */
    public void getUser1(User user1) {
        this.user1 = user1;
    }

    /**
     * Setter for the second user
     * @param user2 - second user
     */
    public void getUser2() {
        this.user2 = user2;
    }

    /**
     * Checks if two Friendships objects are equal, based on their atributes.
     * @param o - the objects to compare with
     * @return true, if the objects are equal
     *         false, otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(user1, that.user1) && Objects.equals(user2, that.user2);
    }

    /**
     * Generates a hash code of the Friendship
     * @return the hash code of the Friendship
     */
    @Override
    public int hashCode() {
        return Objects.hash(user1, user2);
    }
}
