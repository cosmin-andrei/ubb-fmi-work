package domain;

public class Movie extends Entity<Long> {

    private Long id;
    private Long idRegizor;
    private String titlu;
    private int an;

    public Movie(Long id, Long idRegizor, String titlu, int an) {
        this.id = id;
        this.idRegizor = idRegizor;
        this.titlu = titlu;
        this.an = an;
    }

    @Override
    public Long getId() {
        return id;
    }

    @Override
    public void setId(Long id) {
        this.id = id;
    }

    public Long getIdRegizor() {
        return idRegizor;
    }

    public void setIdRegizor(Long idRegizor) {
        this.idRegizor = idRegizor;
    }

    public String getTitlu() {
        return titlu;
    }

    public void setTitlu(String titlu) {
        this.titlu = titlu;
    }

    public int getAn() {
        return an;
    }

    public void setAn(int an) {
        this.an = an;
    }
}
