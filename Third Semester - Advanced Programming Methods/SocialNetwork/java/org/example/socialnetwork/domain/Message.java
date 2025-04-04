package org.example.socialnetwork.domain;

import java.time.LocalDateTime;
import java.util.Objects;

public class Message extends Entity<Long> {
    private User from;
    private User to;
    private String message;
    private LocalDateTime date;
    private Long replyingTo;

    public Message(User from, User to, String message, LocalDateTime dateSend, Long replyingTo) {
        this.from = from;
        this.to = to;
        this.message = message;
        this.date = dateSend;
        this.replyingTo = replyingTo;
    }

    public User getFrom() {
        return from;
    }

    public void setFrom(User from) {
        this.from = from;
    }

    public User getTo() {
        return to;
    }

    public void setTo(User to) {
        this.to = to;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Long getReplyingTo() {
        return replyingTo;
    }

    public void setReplyingTo(Long replyingTo) {
        this.replyingTo = replyingTo;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Message message1 = (Message) o;
        return Objects.equals(getFrom(), message1.getFrom()) && Objects.equals(getTo(), message1.getTo()) && Objects.equals(getMessage(), message1.getMessage()) && Objects.equals(getDate(), message1.getDate()) && Objects.equals(getReplyingTo(), message1.getReplyingTo());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFrom(), getTo(), getMessage(), getDate(), getReplyingTo());
    }

    @Override
    public String toString() {
        return "Message{" +
                "from=" + from +
                ", to=" + to +
                ", message='" + message + '\'' +
                ", date=" + date +
                ", replyingTo=" + replyingTo +
                '}';
    }
}
