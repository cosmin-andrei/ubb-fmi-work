package ro.mpp2024.networking.jsonprotocol;

import com.google.gson.Gson;
import ro.mpp2024.model.Configuratie;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.model.Runda;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientJsonWorker implements Runnable, IObserver {
    private IServices server;
    private Socket connection;

    private BufferedReader input;
    private PrintWriter output;
    private Gson gsonFormatter;
    private volatile boolean connected;

    public ClientJsonWorker(IServices server, Socket connection) {
        this.server = server;
        this.connection = connection;
        gsonFormatter = new Gson();
        try {
            output = new PrintWriter(connection.getOutputStream());
            input = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            connected = true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        while (connected) {
            try {
                String requestLine = input.readLine();
                Request request = gsonFormatter.fromJson(requestLine, Request.class);
                Response response = handleRequest(request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error " + e);
        }
    }

    private static Response okResponse = JsonProtocolUtils.createOkResponse();

    private Response handleRequest(Request request) {
        Response response = null;

        try {
            switch (request.getType()) {
                case LOGIN:
                    Jucator jucator = request.getJucator();
                    server.login(jucator, this);
                    response = okResponse;
                    break;
                case LOGOUT:
                    Jucator jucatorLogout = request.getJucator();
                    server.logout(jucatorLogout, this);
                    connected = false;
                    response = okResponse;
                    break;
                case START_GAME:
                    Jucator jucatorStartGame = request.getJucator();
                    System.out.println("Start game for " + jucatorStartGame.getId());
                    Configuratie c = server.startGame(jucatorStartGame);
                    response = JsonProtocolUtils.createStartGameResponse(c);
                    break;
                case GET_RUNDA:
                    Long id = request.getRunda().getId();
                    response = JsonProtocolUtils.createGetRundaResponse(server.getRunda(id));
                    break;
                case UPDATE_RUNDA:
                    server.updateRunda(request.getRunda());
                    response = okResponse;
                    break;
                case GET_CLASAMENT:
                    response = JsonProtocolUtils.createGetClasamentResponse(server.getClasament());
                    break;
            }
        } catch (ServiceException e) {
            response = JsonProtocolUtils.createErrorResponse(e.getMessage());
        }

        return response;
    }

    private void sendResponse(Response response) throws IOException {
        String responseLine = gsonFormatter.toJson(response);
        System.out.println("sending response " + responseLine);
        synchronized (output) {
            output.println(responseLine);
            output.flush();
        }
    }

    @Override
    public void newRunda(Runda runda) {
        System.out.println("New runda " + runda);
        Response response = JsonProtocolUtils.createNewRundaResponse(runda);
        try {
            sendResponse(response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
