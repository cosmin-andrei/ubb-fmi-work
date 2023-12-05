package ro.ubbcluj.map.socialnetwork.domain;

import java.time.LocalDateTime;

public class CererePrietenie extends Entity<Tuple<Long, Long>>{

    String status;
    LocalDateTime date;

    public CererePrietenie() {
        this.date = LocalDateTime.now();
    }

    public LocalDateTime getDate() {
        return date;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}
