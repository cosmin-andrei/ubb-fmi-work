package ro.mpp2024.networking.jsonprotocol;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
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
import java.util.List;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServicesJsonProxy implements IServices {
    private String host;
    private int port;

    private IObserver client;

    private BufferedReader input;
    private PrintWriter output;
    private Gson gsonFormatter;
    private Socket connection;

    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    public ServicesJsonProxy(String host, int port) throws ServiceException {
        this.host = host;
        this.port = port;
        qresponses = new LinkedBlockingQueue<Response>();
    }

    public void login(Jucator jucator, IObserver client) throws ServiceException {
        initializeConnection();

        Request req = JsonProtocolUtils.createLoginRequest(jucator);
        sendRequest(req);
        Response response = readResponse();
        if (response.getType() == ResponseType.OK) {
            this.client = client;
            return;
        }
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
//            closeConnection();
        }
    }



    public void logout(Jucator jucator, IObserver client) throws ServiceException {

        Request req = JsonProtocolUtils.createLogoutRequest(jucator);
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
    }

    @Override
    public Long chooseMove(Jucator jucator, Map<Long, String> board) throws ServiceException {
        Request req = JsonProtocolUtils.createChooseMoveRequest(jucator, board);
        sendRequest(req);
        Response response = readResponse();
        if(response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
        return response.getMove();
    }

    @Override
    public String verifyGameWin(Map<Long, String> board) throws ServiceException {
        Request req = JsonProtocolUtils.createVerifyGameWinRequest(board);
        sendRequest(req);
        Response response = readResponse();
        if(response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
        return response.getGameWin();

    }

    @Override
    public void addRunda(Runda runda) throws ServiceException {
        Request req = JsonProtocolUtils.createAddRundaRequest(runda);
        sendRequest(req);
        Response response = readResponse();
        if(response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }

    }

    @Override
    public List<Runda> getAllRunda() throws ServiceException {
        Request req = JsonProtocolUtils.createGetAllRundaRequest();
        sendRequest(req);
        Response response = readResponse();
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
        return response.getAllRunda();
    }


    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void sendRequest(Request request) throws ServiceException {
        String reqLine = gsonFormatter.toJson(request);
        try {
            output.println(reqLine);
            output.flush();
            System.out.println("Request sent " + reqLine);
        } catch (Exception e) {
            throw new ServiceException("Error sending object " + e);
        }

    }

    private Response readResponse() throws ServiceException {
        Response response = null;
        try {

            response = qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }

    private void initializeConnection() throws ServiceException {
        try {
            gsonFormatter = new GsonBuilder()
                    .serializeNulls()
                    .create();
            connection = new Socket(host, port);
            output = new PrintWriter(connection.getOutputStream());
            output.flush();
            input = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            finished = false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startReader() {
        Thread tw = new Thread(new ReaderThread());
        tw.start();
    }


    private boolean isUpdate(Response response) {
        return response != null && response.getType() == ResponseType.UPDATE;
    }

    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    String responseLine = input.readLine();
                    System.out.println("response received " + responseLine);
                    Response response = gsonFormatter.fromJson(responseLine, Response.class);
                    if (isUpdate(response)) {
                        handleUpdate(response);
                    } else {
                        try {
                            System.out.printf(String.valueOf(response));
                            qresponses.put(response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Reading error " + e);
                }
            }
        }
    }

    private void handleUpdate(Response response) {
        if (response.getType() == ResponseType.NEW_RUNDA) {
            client.addRunda(response.getRunda());
        }
    }
}

