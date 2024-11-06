package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;

import java.util.List;

public class Request {

    private RequestType type;
    private Jucator jucator;
    private Configuratie configuratie;

    public Jucator getJucator() {
        return jucator;
    }

    public RequestType getType() {
        return type;
    }

    public void setType(RequestType requestType) {
        this.type = requestType;
    }

    public void setJucator(Jucator user) {
        this.jucator = user;
    }

    public void setConfiguratie(Configuratie configuratie) {
        this.configuratie = configuratie;
    }

    public Configuratie getConfiguratie() {
        return configuratie;
    }
}
