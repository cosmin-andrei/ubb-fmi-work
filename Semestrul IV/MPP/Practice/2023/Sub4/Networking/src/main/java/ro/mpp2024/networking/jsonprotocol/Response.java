package ro.mpp2024.networking.jsonprotocol;

import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.io.Serializable;
import java.util.List;

public class Response implements Serializable {

    private ResponseType type;
    private String errorMessage;
    private Jucator jucator;
    private String gameWin;
    private Long move;
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

    public String getGameWin() {
        return gameWin;
    }

    public Long getMove() {
        return move;
    }

    public void setMove(Long move) {
        this.move = move;
    }

    public void setGameWin(String win) {
        this.gameWin = win;
    }

    public Runda getRunda() {
        return runda;
    }

    public void setRunda(Runda runda) {
        this.runda = runda;
    }

    public List<Runda> getAllRunda() {
        return runde;
    }

    public void setAllRunda(List<Runda> runde) {
        this.runde = runde;
    }
}
