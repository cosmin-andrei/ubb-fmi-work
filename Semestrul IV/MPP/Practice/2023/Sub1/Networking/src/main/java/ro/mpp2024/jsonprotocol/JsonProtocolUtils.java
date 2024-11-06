package ro.mpp2024.jsonprotocol;

import ro.mpp2024.Jucator;
import ro.mpp2024.Runda;
import ro.mpp2024.RundaCurenta;

import java.util.List;

public class JsonProtocolUtils {

    public static Response createOkResponse() {
        Response resp = new Response();
        resp.setType(ResponseType.OK);
        return resp;
    }

    public static Request createLoginRequest(Jucator jucator) {
        Request req = new Request();
        req.setType(RequestType.LOGIN);
        req.setJucator(jucator);
        return req;
    }

    public static Response createErrorResponse(String message) {
        Response resp = new Response();
        resp.setType(ResponseType.ERROR);
        resp.setErrorMessage(message);
        return resp;
    }

    public static Request createStartGameRequest(Jucator jucator) {
        Request req = new Request();
        req.setType(RequestType.START_GAME);
        req.setJucator(jucator);
        return req;
    }

    public static Response createRundaCurentaRespone(RundaCurenta rundaC) {
        Response resp = new Response();
        resp.setType(ResponseType.RUNDA_CURENTA);
        resp.setGetGame(rundaC);
        return resp;
    }

    public static Request createAddRundaRequest(Runda runda) {
        Request req = new Request();
        req.setType(RequestType.ADD_RUNDA);
        req.setRunda(runda);
        return req;
    }

    public static Response createGetAllRundeResponse(List<Runda> allRunde) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_ALL_RUNDE);
        resp.setAllRunde(allRunde);
        return resp;
    }

    public static Request createGetAllRundeRequest() {
        Request req = new Request();
        req.setType(RequestType.GET_ALL_RUNDE);
        return req;
    }
}
