//
// Created by Cosmin on 12/8/2024.
//

#ifndef FPTSERVER_SERVER_H
#define FPTSERVER_SERVER_H

#include <winsock2.h>
#include <string>
#include <mutex>

class server {

public:
    server();
    ~server();

    bool start(int port);
    void run() const;
    void stop();

private:
    SOCKET server_socket;
    bool running;

    static void handle_client(SOCKET client_socket);
};

#endif //FPTSERVER_SERVER_H
