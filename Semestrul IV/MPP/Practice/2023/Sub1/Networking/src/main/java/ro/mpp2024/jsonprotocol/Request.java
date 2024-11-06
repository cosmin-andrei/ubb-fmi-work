package ro.mpp2024.jsonprotocol;

import ro.mpp2024.Jucator;
import ro.mpp2024.Runda;

public class Request {

    private RequestType type;
    private Jucator jucator;
    private Runda runda;

    public Request(){}
    public RequestType getType() {
        return type;
    }

    public void setType(RequestType type) {
        this.type = type;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }


    public void setRunda(Runda runda) {
        this.runda = runda;
    }

    public Runda getRunda() {
        return runda;
    }
}
