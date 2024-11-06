package ro.mpp2024.networking.utils;

import ro.mpp2024.networking.jsonprotocol.ClientJsonWorker;
import ro.mpp2024.service.IServices;

import java.net.Socket;

public class JsonConcurrentServer extends AbsConcurrentServer {

    private IServices server;
    public JsonConcurrentServer(int port, IServices server) {
        super(port);
        this.server = server;
        System.out.println("Chat- ChatJsonConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientJsonWorker worker=new ClientJsonWorker(server, client);

        Thread tw=new Thread(worker);
        return tw;
    }

}
