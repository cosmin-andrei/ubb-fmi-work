package chat.network.utils;

import chat.network.jsonprotocol.ChatClientJsonWorker;
import chat.services.IChatServices;

import java.net.Socket;

public class ChatJsonConcurrentServer extends AbsConcurrentServer{
    private IChatServices chatServer;
    public ChatJsonConcurrentServer(int port, IChatServices chatServer) {
        super(port);
        this.chatServer = chatServer;
        System.out.println("Chat- ChatJsonConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ChatClientJsonWorker worker=new ChatClientJsonWorker(chatServer, client);

        Thread tw=new Thread(worker);
        return tw;
    }
}
