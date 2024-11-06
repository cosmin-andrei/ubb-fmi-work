package ro.mpp2024;

import jakarta.persistence.Column;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

import java.io.Serializable;

import static jakarta.persistence.GenerationType.IDENTITY;

@jakarta.persistence.Entity
@Table(name="configuratie")
public class Configuratie implements Entity<Long>, Serializable {

    @Id
    @GeneratedValue(strategy=IDENTITY)
    private Long id;

    @Column(name="linie")
    private Integer linie;

    @Column(name="coloana")
    private Integer coloana;

    @Column(name="indiciu")
    private String indiciu;

    public Configuratie(Integer linie, Integer coloana, String indiciu) {
        this.linie = linie;
        this.coloana = coloana;
        this.indiciu = indiciu;
    }

    public Configuratie() {

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

