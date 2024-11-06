package ro.mpp2024.networking.jsonprotocol;


import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;

import java.util.List;
import java.util.Map;

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

    public static Request createVerifyGameWinRequest(Map<Long, String> board) {
        Request req = new Request();
        req.setType(RequestType.VERIFY_GAME_WIN);
        req.setBoard(board);
        return req;
    }

    public static Request createChooseMoveRequest(Jucator jucator, Map<Long, String> board) {
        Request req = new Request();
        req.setType(RequestType.CHOOSE_MOVE);
        req.setJucator(jucator);
        req.setBoard(board);
        return req;
    }

    public static Response createMoveResponse(Long move) {
        Response resp = new Response();
        resp.setType(ResponseType.MOVE);
        resp.setMove(move);
        return resp;
    }

    public static Response createVerifyGameWinResponse(String win) {
        Response resp = new Response();
        resp.setType(ResponseType.VERIFY_GAME_WIN);
        resp.setGameWin(win);
        return resp;
    }

    public static Request createAddRundaRequest(Runda runda) {
        Request req = new Request();
        req.setType(RequestType.NEW_RUNDA);
        req.setRunda(runda);
        return req;
    }

    public static Response createAddRundaResponse(Runda runda) {
        Response resp = new Response();
        resp.setType(ResponseType.NEW_RUNDA);
        resp.setRunda(runda);
        return resp;
    }

    public static Request createGetAllRundaRequest() {
        Request req = new Request();
        req.setType(RequestType.GET_ALL_RUNDA);
        return req;
    }

    public static Response createGetAllRundaResponse(List<Runda> allRunda) {
        Response resp = new Response();
        resp.setType(ResponseType.GET_ALL_RUNDA);
        resp.setAllRunda(allRunda);
        return resp;
    }
}
