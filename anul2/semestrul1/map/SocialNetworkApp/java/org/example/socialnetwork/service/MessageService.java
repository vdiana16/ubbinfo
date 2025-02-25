package org.example.socialnetwork.service;

import org.example.socialnetwork.domain.*;
import org.example.socialnetwork.repository.Repository;
import org.example.socialnetwork.utils.events.ChangeEventType;
import org.example.socialnetwork.utils.events.SocialNetworkChangeEvent;
import org.example.socialnetwork.utils.observer.Observable;
import org.example.socialnetwork.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class MessageService implements Observable<SocialNetworkChangeEvent> {
    private final Repository<Long, User> userRepository;
    private final Repository<Long, Friendship> friendshipRepository;
    private final Repository<Long, Message> messageRepository;
    private List<Observer<SocialNetworkChangeEvent>> observers = new ArrayList<>();

    public MessageService(Repository<Long, User> userRepository, Repository<Long, Friendship> friendshipRepository,
                          Repository<Long, Message> messageRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.messageRepository = messageRepository;
    }

    public List<Message> getAllMessages() {
        return (List<Message>) messageRepository.findAll();
    }

    public List<Message> getMessagesForUser(User user) {
        return getAllMessages().stream()
                .filter(m->m.getTo().equals(user))
                .collect(Collectors.toList());
    }

    public List<Message> getMessagesFromUser(User user) {
        return getAllMessages().stream()
                .filter(m->m.getFrom().equals(user))
                .collect(Collectors.toList());
    }

    public List<Message> getMessagesBetweenUsers(User u1, User u2) {
        List<Message> conv = getAllMessages().stream()
                .filter(m->m.getFrom().equals(u1) && m.getTo().equals(u2) || m.getFrom().equals(u2) && m.getTo().equals(u1))
                .collect(Collectors.toList());
        conv.sort(Comparator.comparing(Message::getDate));
        return conv;
    }

    public void sendMessage(User from, User to, String message, Long replyingTo) {
        Message mes = new Message(from, to, message, LocalDateTime.now(), replyingTo);
        messageRepository.save(mes);
        notifyObservers(new SocialNetworkChangeEvent<>(ChangeEventType.ADDMESSAGE, mes));
    }

    public void deleteMessage(Message message) {
        messageRepository.delete(message.getId());
        notifyObservers(new SocialNetworkChangeEvent<>(ChangeEventType.DELETEMESSAGE, message));
    }

    @Override
    public void addObserver(Observer<SocialNetworkChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<SocialNetworkChangeEvent> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(SocialNetworkChangeEvent socialNetworkChangeEvent) {
        observers.stream().forEach(observer -> observer.update(socialNetworkChangeEvent));
    }
}
