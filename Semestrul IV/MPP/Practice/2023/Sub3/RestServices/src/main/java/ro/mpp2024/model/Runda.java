package ro.mpp2024.model;

import jakarta.persistence.Column;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

import java.io.Serializable;

@jakarta.persistence.Entity
@Table(name = "Runde")
public class Runda implements Entity<Long>, Serializable {

    private Long id;

    @Column(name = "jucator")
    private String jucator;

    @Column(name = "scor")
    private int scor;

    @Column(name = "durata")
    private Long durata;


    public Runda(String jucator, int scor, Long durata) {
        this.jucator = jucator;
        this.scor = scor;
        this.durata = durata;
    }

    public Runda() {

    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }

    @Id
    @GeneratedValue(generator = "increment")
    public Long getId() {
        return id;
    }

    public String getJucator() {
        return jucator;
    }

    public void setJucator(String jucator) {
        this.jucator = jucator;
    }

    public int getScor() {
        return scor;
    }

    public void setScor(int scor) {
        this.scor = scor;
    }

    public Long getDurata() {
        return durata;
    }

    public void setDurata(Long durata) {
        this.durata = durata;
    }

    //    @Override
//    public String toString() {
//        return "Runda{" +
//                "id=" + id +
//                ", jucator=" + jucator +
//                ", scor=" + scor +
//                ", durata=" + durata +
//                '}';
//    }
}
