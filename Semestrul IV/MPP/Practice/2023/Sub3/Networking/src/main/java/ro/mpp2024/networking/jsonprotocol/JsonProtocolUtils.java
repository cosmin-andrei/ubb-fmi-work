package ro.mpp2024.networking.jsonprotocol;


import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.List;

public class JsonProtocolUtils {

    public static Request createLoginRequest(Jucator user) {
        Request req = new Request();
        req.setType(RequestType.LOGIN);
        req.setJucator(user);
        return req;
    }

    public static Response createErrorResponse(String errorMessage) {
        Response resp = new Response();
        resp.setType(ResponseType.ERROR);
        resp.setErrorMessage(errorMessage);
        return resp;
    }

    public static Response createOkResponse() {
        Response resp = new Response();
        resp.setType(ResponseType.OK);
        return resp;
    }

    public static Request createLogoutRequest(Jucator user) {
        Request req = new Request();
        req.setType(RequestType.LOGOUT);
        req.setJucator(user);
        return req;
    }

    public static Request createStartGameRequest(Jucator jucator) {
        Request req = new Request();
        req.setType(RequestType.START_GAME);
        req.setJucator(jucator);
        return req;
    }

    public static Request createGetRundaRequest(Long id) {
        Request req = new Request();
        req.setType(RequestType.GET_RUNDA);
        Runda runda = new Runda(new Jucator(""), 0);
        runda.setId(id);
        req.setRunda(runda);
        return req;
    }

    public static Response createGetRundaResponse(Runda runda) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_RUNDA);
        resp.setRunda(runda);
        return resp;
    }

    public static Response createStartGameResponse(Configuratie c) {
        Response resp = new Response();
        resp.setType(ResponseType.START_GAME);
        resp.setConfiguratie(c);
        return resp;
    }

    public static Response createNewRundaResponse(Runda runda) {
        Response resp = new Response();
        resp.setType(ResponseType.NEW_RUNDA);
        resp.setRunda(runda);
        return resp;
    }

    public static Response createGetClasamentResponse(List<Runda> clasament) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_CLASAMENT);
        resp.setRunde(clasament);
        return resp;
    }
}
