package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.Map;

public class Request {

    private RequestType type;
    private Jucator jucator;
    private Map<Long, String> board;
    private Runda runda;

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

    public void setBoard(Map<Long, String> board) {
        this.board = board;
    }

    public Map<Long, String> getBoard() {
        return board;
    }

    public void setRunda(Runda runda) {
        this.runda = runda;
    }

    public Runda getRunda() {
        return runda;
    }
}
