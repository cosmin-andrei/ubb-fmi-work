package ro.mpp2024;

import java.io.Serializable;
import java.sql.Timestamp;
import java.time.LocalDateTime;

public class RundaCurenta implements Entity<Long>, Serializable {

    private Long id;
    private Jucator jucator;
    private Integer scor;
    private String indiciu;
    private Integer linie;
    private Integer coloana;
    private Timestamp data;

    public RundaCurenta(Jucator jucator, Integer scor, String indiciu, Integer linie, Integer coloana) {
        this.jucator = jucator;
        this.scor = scor;
        this.indiciu = indiciu;
        this.linie = linie;
        this.coloana = coloana;
        this.data = Timestamp.valueOf(LocalDateTime.now());
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public Integer getScor() {
        return scor;
    }

    public void setScor(Integer scor) {
        this.scor = scor;
    }

    public String getIndiciu() {
        return indiciu;
    }

    public void setIndiciu(String indiciu) {
        this.indiciu = indiciu;
    }

    public Integer getLinie() {
        return linie;
    }

    public void setLinie(Integer linie) {
        this.linie = linie;
    }

    public Integer getColoana() {
        return coloana;
    }

    public void setColoana(Integer coloana) {
        this.coloana = coloana;
    }

    public Timestamp getData() {
        return data;
    }

    public void setData(Timestamp data) {
        this.data = data;
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
