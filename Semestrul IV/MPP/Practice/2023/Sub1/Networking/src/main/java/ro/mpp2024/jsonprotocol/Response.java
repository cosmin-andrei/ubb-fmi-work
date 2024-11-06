package ro.mpp2024.jsonprotocol;

import ro.mpp2024.Jucator;
import ro.mpp2024.Runda;
import ro.mpp2024.RundaCurenta;

import java.util.List;

public class Response {

    public RundaCurenta getGame;
    private ResponseType type;
    private String errorMessage;
    private Jucator jucator;
    private List<Runda> allRunde;

    public Response(){}
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

    public RundaCurenta getGetGame() {
        return getGame;
    }

    public void setGetGame(RundaCurenta getGame) {
        this.getGame = getGame;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void setAllRunde(List<Runda> allRunde) {
        this.allRunde = allRunde;
    }

    public List<Runda> getAllRunde() {
        return allRunde;
    }
}
