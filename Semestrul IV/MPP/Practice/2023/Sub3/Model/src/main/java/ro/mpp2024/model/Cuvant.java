package ro.mpp2024.model;

import java.io.Serializable;

public class Cuvant implements Entity<String>, Serializable {

    private String cuvant;


    @Override
    public void setId(String s) {
        this.cuvant = s;
    }

    @Override
    public String getId() {
        return cuvant;
    }

}
