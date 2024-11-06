package ro.mpp2024.jsonprotocol;

import com.google.gson.Gson;
import ro.mpp2024.*;

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


    private void sendResponse(Response response) {
        String responseLine=gsonFormatter.toJson(response);
        System.out.println("sending response "+responseLine);
        synchronized (output) {
            output.println(responseLine);
            output.flush();
        }
    }

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
                    Jucator logoutJucator = request.getJucator();
                    server.logout(logoutJucator, this);
                    connected = false;
                    response = okResponse;
                    break;
                case START_GAME:
                    Jucator startGameJucator = request.getJucator();
                    RundaCurenta rundaC = server.startGame(startGameJucator);
                    response = JsonProtocolUtils.createRundaCurentaRespone(rundaC);
                    break;
                case ADD_RUNDA:
                    Runda runda = request.getRunda();
                    server.addRunda(runda);
                    response = okResponse;
                    break;
                case GET_ALL_RUNDE:
                    response = JsonProtocolUtils.createGetAllRundeResponse(server.getAllRunde());
                    break;

            }
        } catch (ServiceException e) {
            response = JsonProtocolUtils.createErrorResponse(e.getMessage());
        }

        return response;

    }

    @Override
    public void newRunda(Runda runda) {

    }
}
