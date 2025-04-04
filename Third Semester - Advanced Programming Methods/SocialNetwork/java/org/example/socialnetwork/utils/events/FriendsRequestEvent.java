package org.example.socialnetwork.utils.events;

import org.example.socialnetwork.domain.User;

public class FriendsRequestEvent extends SocialNetworkChangeEvent {
    private final User sender;
    private final User receiver;

    public FriendsRequestEvent(User sender, User receiver) {
        super(ChangeEventType.ADD, receiver);
        this.sender = sender;
        this.receiver = receiver;
    }

    public User getSender() {
        return sender;
    }

    public User getReceiver() {
        return receiver;
    }
}