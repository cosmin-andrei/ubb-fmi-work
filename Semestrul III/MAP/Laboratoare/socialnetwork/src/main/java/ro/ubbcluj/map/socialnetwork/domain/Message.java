package ro.ubbcluj.map.socialnetwork.domain;

import java.time.LocalDateTime;
import java.util.UUID;

public class Message extends Entity<UUID> {

    private String text;
    private Utilizator sender;
    private Utilizator receiver;
    private LocalDateTime date;

    public Message(String text, Utilizator sender, Utilizator receiver, LocalDateTime date) {
        this.text = text;
        this.sender = sender;
        this.receiver = receiver;
        this.date = date;
    }

    public String getText() {
        return text;
    }

    public Utilizator getSender() {
        return sender;
    }

    public Utilizator getReceiver() {
        return receiver;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setText(String text) {
        this.text = text;
    }

    public void setSender(Utilizator sender) {
        this.sender = sender;
    }

    public void setReceiver(Utilizator receiver) {
        this.receiver = receiver;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}
