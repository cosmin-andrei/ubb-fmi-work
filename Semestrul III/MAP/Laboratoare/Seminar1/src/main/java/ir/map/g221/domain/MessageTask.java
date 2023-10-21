package ir.map.g221.domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String mesaj;
    private String from;
    private String to;
    private LocalDateTime date;
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy:MM:dd-hh:mm:ss");

    public MessageTask(String taskID, String descriere, String mesaj, String from, String to, LocalDateTime date) {
        super(taskID, descriere);
        this.mesaj = mesaj;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void run() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        var format = DateTimeFormatter.ofPattern("yyyy:MM:dd-hh:mm:ss").format(date);
        return "MessageTask{" +
                "mesaj='" + mesaj + '\'' +
                ", from='" + from + '\'' +
                ", to='" + to + '\'' +
                ", date=" + format +
                '}';
    }
}
