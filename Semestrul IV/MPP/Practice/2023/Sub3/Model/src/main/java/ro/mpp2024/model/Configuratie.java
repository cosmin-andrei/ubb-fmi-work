package ro.mpp2024.model;

import java.io.Serializable;

public class Configuratie implements Entity<Long>, Serializable {

    private Long id;
    private Cuvant poz1;
    private Cuvant poz2;
    private Cuvant poz3;
    private Cuvant poz4;
    private Cuvant poz5;
    private Cuvant poz6;
    private Cuvant poz7;
    private Cuvant poz8;
    private Cuvant poz9;
    private Cuvant poz10;
    private Runda runda;

    public Configuratie(Cuvant poz1, Cuvant poz2, Cuvant poz3, Cuvant poz4, Cuvant poz5, Cuvant poz6, Cuvant poz7, Cuvant poz8, Cuvant poz9, Cuvant poz10) {
        this.poz1 = poz1;
        this.poz2 = poz2;
        this.poz3 = poz3;
        this.poz4 = poz4;
        this.poz5 = poz5;
        this.poz6 = poz6;
        this.poz7 = poz7;
        this.poz8 = poz8;
        this.poz9 = poz9;
        this.poz10 = poz10;
    }

    public Runda getRunda() {
        return runda;
    }

    public void setRunda(Runda runda) {
        this.runda = runda;
    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }

    @Override
    public Long getId() {
        return id;
    }

    public Cuvant getPoz1() {
        return poz1;
    }

    public void setPoz1(Cuvant poz1) {
        this.poz1 = poz1;
    }

    public Cuvant getPoz2() {
        return poz2;
    }

    public void setPoz2(Cuvant poz2) {
        this.poz2 = poz2;
    }

    public Cuvant getPoz3() {
        return poz3;
    }

    public void setPoz3(Cuvant poz3) {
        this.poz3 = poz3;
    }

    public Cuvant getPoz4() {
        return poz4;
    }

    public void setPoz4(Cuvant poz4) {
        this.poz4 = poz4;
    }

    public Cuvant getPoz5() {
        return poz5;
    }

    public void setPoz5(Cuvant poz5) {
        this.poz5 = poz5;
    }

    public Cuvant getPoz6() {
        return poz6;
    }

    public void setPoz6(Cuvant poz6) {
        this.poz6 = poz6;
    }

    public Cuvant getPoz7() {
        return poz7;
    }

    public void setPoz7(Cuvant poz7) {
        this.poz7 = poz7;
    }

    public Cuvant getPoz8() {
        return poz8;
    }

    public void setPoz8(Cuvant poz8) {
        this.poz8 = poz8;
    }

    public Cuvant getPoz9() {
        return poz9;
    }

    public void setPoz9(Cuvant poz9) {
        this.poz9 = poz9;
    }

    public Cuvant getPoz10() {
        return poz10;
    }

    public void setPoz10(Cuvant poz10) {
        this.poz10 = poz10;
    }
}
