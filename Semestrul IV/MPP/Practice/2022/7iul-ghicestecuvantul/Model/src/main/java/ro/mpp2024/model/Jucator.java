package ro.mpp2024.model;

import java.io.Serializable;

public class Jucator implements Entity<String>, Serializable {

    private String alias;

    @Override
    public void setId(String s) {
        this.alias=s;
    }

    @Override
    public String getId() {
        return alias;
    }

    public Jucator(String alias) {
        this.alias = alias;
    }
}