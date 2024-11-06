package ro.mpp2024.model;

import jakarta.persistence.Column;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;

import java.io.Serializable;

@jakarta.persistence.Entity
@jakarta.persistence.Table(name = "Configuratii")
public class Configuratie implements ro.mpp2024.model.Entity<Long>, Serializable {

    @Id
    @GeneratedValue(generator = "increment")
    private Long id;

    @Column(name = "model")
    private String model;

    @Column(name = "player")
    private String player;

    public Configuratie(String model, String player) {
        this.model = model;
        this.player = player;
    }

    public Configuratie() {

    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }

    @Override
    public Long getId() {
        return id;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getPlayer() {
        return player;
    }

    public void setPlayer(String player) {
        this.player = player;
    }
}
