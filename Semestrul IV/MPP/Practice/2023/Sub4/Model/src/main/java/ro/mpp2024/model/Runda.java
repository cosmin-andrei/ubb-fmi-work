//package ro.mpp2024.model;
//
//import jakarta.persistence.*;
//
//import java.io.Serializable;
//
//@jakarta.persistence.Entity
//@Table(name = "runde")
//public class Runda implements ro.mpp2024.model.Entity<Long>, Serializable {
//
//    @Id
//    @GeneratedValue(generator = "increment")
//    private Long id;
//
//    @Column(name = "player")
//    private String player;
//
//    @Column(name = "scor")
//    private int scor;
//
//    @Column(name = "durata")
//    private int durata;
//
//    public Runda() {
//    }
//
//
//    public void setId(Long aLong) {
//        this.id = aLong;
//    }
//
//    public Long getId() {
//        return id;
//    }
//
//    public Runda(String player, int scor, int durata) {
//        this.player = player;
//        this.scor = scor;
//        this.durata = durata;
//    }
//
//    public String getPlayer() {
//        return player;
//    }
//
//    public void setPlayer(String player) {
//        this.player = player;
//    }
//
//    public int getScor() {
//        return scor;
//    }
//
//    public void setScor(int scor) {
//        this.scor = scor;
//    }
//
//    public int getDurata() {
//        return durata;
//    }
//
//    public void setDurata(int durata) {
//        this.durata = durata;
//    }
//}
