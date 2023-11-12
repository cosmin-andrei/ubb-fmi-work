package domain;

public class Regizor extends Entity<Long>{

    private Long idRegizor;
    private String nume;

    public Regizor(Long idRegizor, String nume) {
        this.idRegizor = idRegizor;
        this.nume = nume;
    }

    public Long getIdRegizor() {
        return idRegizor;
    }

    public void setIdRegizor(Long idRegizor) {
        this.idRegizor = idRegizor;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }
}
