package ro.mpp2024;

import java.io.Serializable;
import java.sql.Time;
import java.sql.Timestamp;
import java.time.LocalDateTime;

public class Runda implements Entity<Long>, Serializable {

    private Long id;
    private Jucator jucator;
    private Timestamp data;
    private Integer nr_incercari;
    private String indiciu;

    public Runda(Jucator jucator, Timestamp data, Integer nr_incercari, String indiciu) {
        this.jucator = jucator;
        this.data = data;
        this.nr_incercari = nr_incercari;
        this.indiciu = indiciu;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public Timestamp getData() {
        return data;
    }

    public void setData(Timestamp data) {
        this.data = data;
    }

    public Integer getNr_incercari() {
        return nr_incercari;
    }

    public void setNr_incercari(Integer nr_incercari) {
        this.nr_incercari = nr_incercari;
    }

    public String getIndiciu() {
        return indiciu;
    }

    public void setIndiciu(String indiciu) {
        this.indiciu = indiciu;
    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }

    @Override
    public Long getId() {
        return id;
    }
}
