package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;

import java.io.Serializable;
import java.util.List;

public class Response implements Serializable {

    private ResponseType type;
    private String errorMessage;
    private Jucator jucator;
    private List<Jucator> jucatori;
    private String propunere;
    private Configuratie configuratie;

    public Response() {
    }

    public ResponseType getType() {
        return type;
    }

    public void setType(ResponseType type) {
        this.type = type;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public List<Jucator> getJucatori() {
        return jucatori;
    }

    public void setJucatori(List<Jucator> jucatori) {
        this.jucatori = jucatori;
    }

    public String getPropuneri() {
        return propunere;
    }

    public void setPropuneri(String propuneri) {
        this.propunere = propuneri;
    }

    public Configuratie getConfiguratie() {
        return configuratie;
    }

    public void setConfiguratie(Configuratie configuratie) {
        this.configuratie = configuratie;
    }
}
