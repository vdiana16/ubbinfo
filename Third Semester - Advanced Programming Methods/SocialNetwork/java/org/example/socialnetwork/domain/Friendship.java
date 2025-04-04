package org.example.socialnetwork.domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

/**
 * Class representing a Friendship between two users.
 */
public class Friendship extends Entity<Long> {
    private final User user1;     //The first user.
    private final User user2;     //The second user.
    private LocalDateTime date;
    private FriendshipStatus status;

    /**
     * Constructor for creating a Friendship object.
     * @param user1 - The first user
     * @param user2 - The second user
     */
    public Friendship(User user1, User user2, LocalDateTime date, FriendshipStatus status) {
        this.user1 = user1;
        this.user2 = user2;
        this.date = date;
        this.status = status;
    }

    public FriendshipStatus getStatus() {
        return status;
    }

    public void setStatus(FriendshipStatus status) {
        this.status = status;
    }

    /**
     * Getter for the first user
     * @return user1 the first user
     */
    public User getUser1() {
        return user1;
    }

    /**
     * Getter for the second user
     * @return user2 the second user
     */
    public User getUser2() {
        return user2;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    private String formatter(LocalDateTime date) {
        String timetoprint;
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        timetoprint = date.format(formatter);
        return timetoprint;
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "User='" + user1.getFirstName() + '\'' +
                ", lastName='" + user1.getLastName() + '\'' + " with User='" + user2.getFirstName() + '\'' +
                ", lastName='" + user2.getLastName() + '\'' + " Date = " + formatter(date) + '}';
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
