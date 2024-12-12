#include <ws2tcpip.h>
#include "server.h"
#include "handle_cmd.h"
#include <cstring>
#include <iostream>

#define BUFFER_SIZE 1024 //buffer for data received

server::server() : server_socket(INVALID_SOCKET), running(false) {}

server::~server() {
    stop();
}

bool server::start(int port) {

    //init WinSock - Windows Sockets - API for network apps in Windows
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("Eroare: init WinSock");
        return false;
    }

    //create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Eroare: creare socket");
        WSACleanup();
        return false;
    }

    //config server
    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    //socket to port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Eroare: bind");
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    //socket to listen (max 5 clients)
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        perror("Eroare: listen");
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    running = true; //server is running
    return true;
}

void server::run() const {
    while (running) {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);

        //accept client
        SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

        if (client_socket == INVALID_SOCKET) {
            perror("Eroare: accept");
            continue;
        }

        std::cout << "Client conectat.\n";
        handle_client(client_socket);
        closesocket(client_socket);
    }
}

void server::stop() {
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket);
        WSACleanup();
        server_socket = INVALID_SOCKET;
    }
    running = false;
}

//sanitizare cod
void trim(std::string &str) {

    //spatii de inceput
    while (!str.empty() && std::isspace(str.front())) {
        str.erase(str.begin());
    }

    //spatii de final
    while (!str.empty() && std::isspace(str.back())) {
        str.pop_back();
    }
}

//handle client
void server::handle_client(SOCKET client_socket) {
    handle_cmd commands(client_socket); //handle commands

    //send welcome message
    std::cout << "[DEBUG] Sending welcome message..." << std::endl;
    commands.send_response("220 Welcome to FTP Server\r\n");

    char buffer[BUFFER_SIZE]; //buffer for data received

    while (true) {
        memset(buffer, 0, BUFFER_SIZE); //reset buffer
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received <= 0) {
            std::cout << "Client deconectat.\n";
            break;
        }

        std::string command(buffer); //buffer->string
        trim(command);
        std::cout << "Comanda: " << command << '\n';

        if (!commands.process_command(command)) {
            break;
        }
    }
}