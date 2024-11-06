package ro.mpp2024.model;

import java.io.Serializable;

public class Runda implements Entity<Long>, Serializable {

    private Long id;
    private Jucator jucator;
    private int scor;
    private Long durata;

    public Runda(Jucator jucator, int scor) {
        this.jucator = jucator;
        this.scor = scor;
        this.durata = 0L;
    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }

    @Override
    public Long getId() {
        return id;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public int getScor() {
        return scor;
    }

    public void setScor(int scor) {
        this.scor = scor;
    }

    public long getDurata() {
        return durata;
    }

    public void setDurata(long durata) {
        this.durata = durata;
    }
}
