package ro.mpp2024.networking.jsonprotocol;


import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;

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

    public static Response createGetJucatoriResponse(List<Jucator> jucatori) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_JUCATORI);
        resp.setJucatori(jucatori);
        return resp;
    }

    public static Response createGetPropuneriResponse(String propuneri) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_PROPUNERI);
        resp.setPropuneri(propuneri);
        return resp;
    }

    public static Response createGetConfiguratieResponse(Configuratie configuratie) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_CONFIGURATIE);
        resp.setConfiguratie(configuratie);
        return resp;
    }

    public Request createGetJucatoriRequest() {
        Request req = new Request();
        req.setType(RequestType.GET_JUCATORI);
        return req;
    }

    public Request createGetPropuneriRequest() {
        Request req = new Request();
        req.setType(RequestType.GET_PROPUNERI);
        return req;
    }

    public Request createSaveConfigurationRequest(Configuratie configuratie) {
        Request req = new Request();
        req.setType(RequestType.SAVE_CONFIGURATION);
        req.setConfiguratie(configuratie);
        return req;
    }

    public Request createGetConfiguratieRequest(String id) {
        Request req = new Request();
        req.setType(RequestType.GET_CONFIGURATIE);
        Configuratie configuratie = new Configuratie("",id);
        req.setConfiguratie(configuratie);
        return req;
    }
}
