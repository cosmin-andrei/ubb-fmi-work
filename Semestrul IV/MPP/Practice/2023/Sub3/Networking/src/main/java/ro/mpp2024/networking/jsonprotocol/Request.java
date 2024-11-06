package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.List;

public class Request {

    private RequestType type;
    private Jucator jucator;
    private Runda runda;
    private List<Runda> runde;

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

    public void setRunda(Runda runda) {
        this.runda = runda;
    }

    public Runda getRunda() {
        return runda;
    }

    public List<Runda> getRunde() {
        return runde;
    }

    public void setRunde(List<Runda> runde) {
        this.runde = runde;
    }
}
