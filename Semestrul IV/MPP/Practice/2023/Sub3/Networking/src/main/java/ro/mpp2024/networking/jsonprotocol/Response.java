package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.io.Serializable;
import java.util.List;

public class Response implements Serializable {

    private ResponseType type;
    private String errorMessage;
    private Jucator jucator;
    private Configuratie configuratie;
    private Runda runda;
    private List<Runda> runde;

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

    public Configuratie getGetGame() {
        return configuratie;
    }

    public void setConfiguratie(Configuratie configuratie) {
        this.configuratie = configuratie;
    }

    public Runda getRunda() {
        return runda;
    }

    public void setRunda(Runda r) {
        this.runda = r;
    }

    public List<Runda> getAllRunde() {
        return runde;
    }

    public void setRunde(List<Runda> runde) {
        this.runde = runde;
    }
}
