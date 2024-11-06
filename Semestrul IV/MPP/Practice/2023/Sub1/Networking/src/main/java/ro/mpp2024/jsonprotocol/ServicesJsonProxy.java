package ro.mpp2024.jsonprotocol;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import ro.mpp2024.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;
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

    @Override
    public void login(Jucator jucator, IObserver client) throws ServiceException {
        initializeConnection();
        Request req = JsonProtocolUtils.createLoginRequest(jucator);
        sendRequest(req);
        System.out.println("Request sent");
        Response response = readResponse();
        if (response.getType() == ResponseType.OK) {
            this.client = client;
            System.out.println("Login successful" + client);
            return;
        }
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            closeConnection();
            throw new ServiceException(err);
        }

    }

    private void initializeConnection() {
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

    private boolean isUpdate(Response response) {
        return response != null && (response.getType() == ResponseType.NEW_RUNDA);
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

    private Response readResponse() {
        Response response = null;
        try {

            response = qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
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


    private void handleUpdate(Response response) {
        if (response.getType() == ResponseType.NEW_RUNDA) {
            System.out.println("New round started");
        }
    }

    private void startReader() {
        Thread tw = new Thread(new ReaderThread());
        tw.start();
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

    @Override
    public void logout(Jucator jucator, IObserver client) throws ServiceException {

    }

    @Override
    public RundaCurenta startGame(Jucator jucator) throws ServiceException {
        Request req = JsonProtocolUtils.createStartGameRequest(jucator);
        sendRequest(req);
        Response response = readResponse();
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
        return response.getGetGame();
    }

    @Override
    public void addRunda(Runda runda) throws ServiceException {
        Request req = JsonProtocolUtils.createAddRundaRequest(runda);
        sendRequest(req);
    }

    @Override
    public List<Runda> getAllRunde() throws ServiceException {
        Request req = JsonProtocolUtils.createGetAllRundeRequest();
        sendRequest(req);
        Response response = readResponse();
        if (response.getType() == ResponseType.ERROR) {
            String err = response.getErrorMessage();
            throw new ServiceException(err);
        }
        return response.getAllRunde();
    }
}
