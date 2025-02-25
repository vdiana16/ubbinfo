package org.example.socialnetwork.utils.events;


import org.example.socialnetwork.domain.Friendship;
import org.example.socialnetwork.domain.FriendshipStatus;

public class FriendshipStatusEvent implements Event {
    private FriendshipStatus status;
    private Friendship friendship;

    public FriendshipStatusEvent(FriendshipStatus status, Friendship friendship) {
        this.status = status;
        this.friendship = friendship;
    }

    public FriendshipStatus getStatus() {
        return status;
    }

    public void setStatus(FriendshipStatus status) {
        this.status = status;
    }

    public Friendship getFriendship() {
        return friendship;
    }

    public void setFriendship(Friendship friendship) {
        this.friendship = friendship;
    }
}
