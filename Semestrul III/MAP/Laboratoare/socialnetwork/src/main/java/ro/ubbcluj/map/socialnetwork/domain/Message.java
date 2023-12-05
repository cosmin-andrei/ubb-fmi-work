package ro.ubbcluj.map.socialnetwork.domain;

import java.time.LocalDateTime;

public class Message extends Entity<Long> {

    private String text;
    private Long idSender;
    private Long idReceiver;
    private LocalDateTime date;

    public Message() {
        this.date = LocalDateTime.now();
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public Long getIdSender() {
        return idSender;
    }

    public void setIdSender(Long idSender) {
        this.idSender = idSender;
    }

    public Long getIdReceiver() {
        return idReceiver;
    }

    public void setIdReceiver(Long idReceiver) {
        this.idReceiver = idReceiver;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}