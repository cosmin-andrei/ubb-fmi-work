package ro.mpp2024.networking.jsonprotocol;

import com.google.gson.Gson;
import ro.mpp2024.model.Jucator;
import ro.mpp2024.service.IObserver;
import ro.mpp2024.service.IServices;
import ro.mpp2024.service.ServiceException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;

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
        gsonFormatter=new Gson();
        try{
            output=new PrintWriter(connection.getOutputStream());
            input=new BufferedReader(new InputStreamReader(connection.getInputStream()));
            connected=true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        while(connected){
            try {
                String requestLine=input.readLine();
                Request request=gsonFormatter.fromJson(requestLine, Request.class);
                Response response=handleRequest(request);
                if (response!=null){
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
            System.out.println("Error "+e);
        }
    }

    private static Response okResponse=JsonProtocolUtils.createOkResponse();

    private Response handleRequest(Request request) {
        Response response=null;

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
                case GET_JUCATORI:
                    List<Jucator> jucatori = server.getJucatori();
                    response = JsonProtocolUtils.createGetJucatoriResponse(jucatori);
                    break;
                case GET_PROPUNERI:
                    String propuneri = server.getPropuneri();
                    response = JsonProtocolUtils.createGetPropuneriResponse(propuneri);
                    break;
                case SAVE_CONFIGURATION:
                    server.saveConfiguration(request.getConfiguratie());
                    response = okResponse;
                    break;
                case GET_CONFIGURATION:
                    response = JsonProtocolUtils.createGetConfiguratieResponse(server.getConfiguratie(request.getConfiguratie().getPlayer()));
                    break;
            }
        } catch (ServiceException e) {
            response = JsonProtocolUtils.createErrorResponse(e.getMessage());
        }

        return response;
    }

    private void sendResponse(Response response) throws IOException{
        String responseLine=gsonFormatter.toJson(response);
        System.out.println("sending response "+responseLine);
        synchronized (output) {
            output.println(responseLine);
            output.flush();
        }
    }
}