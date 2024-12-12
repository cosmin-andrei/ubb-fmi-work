#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>
#include "handle_cmd.h"
#include <direct.h>  // For _getcwd on Windows

handle_cmd::handle_cmd(SOCKET client_socket)
        : client_socket(client_socket), authenticated(false), passive_socket(INVALID_SOCKET), active_mode(false),
          active_addr{} {}

          // Destructor - for passive socket
handle_cmd::~handle_cmd() {
    if (passive_socket != INVALID_SOCKET) closesocket(passive_socket);
}

std::map<std::string, std::string> config;

//load config server (user, password)
void handle_cmd::load_config(const std::string &file_name) {
    std::ifstream config_file(file_name);
    if (!config_file.is_open()) {
        throw std::runtime_error("Eroare: config file - not opened.");
    }

    std::string line;
    while (std::getline(config_file, line)) {
        //key-val
        //save in map
        auto delimiter_pos = line.find('=');
        if (delimiter_pos == std::string::npos) continue;

        std::string key = line.substr(0, delimiter_pos);
        std::string value = line.substr(delimiter_pos + 1);
        config[key] = value;
    }

    config_file.close();
}

//send response to client
void handle_cmd::send_response(const char *response) const {

    size_t response_length = strlen(response);

    //prevent overflow - aveam avertizare de la clion
    if (response_length > static_cast<size_t>(std::numeric_limits<int>::max())) {
        std::cerr << "[ERROR] Response size exceeds maximum int value" << std::endl;
        return;
    }

    int response_size = static_cast<int>(response_length);
    //send resp
    int bytesSent = send(client_socket, response, response_size, 0);

    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "[ERROR] Failed to send response: " << WSAGetLastError() << std::endl;
    } else {
        std::cout << "[DEBUG] Response sent: " << response << std::endl;
    }
}

//process cmd from client
bool handle_cmd::process_command(const std::string &cmd) {
    if (cmd.starts_with("USER")) {
        handle_user(cmd.substr(5));
    } else if (cmd.starts_with("PASS")) {
        handle_pass(cmd.substr(5));
    } else if (cmd.starts_with("QUIT")) {
        handle_exit();
        return false;
    } else if (!authenticated) {
        send_response("530 Login with USER and PASS.\r\n");
        return true;
    } else if (cmd.starts_with("LIST")) {
        handle_list();
    } else if (cmd.starts_with("PASV")) {
        handle_pasv();
    } else if (cmd.starts_with("PWD") || cmd.starts_with("CWD")) {
        handle_pwd(); //return current dir
    } else if (cmd.starts_with("TYPE")) {
        handle_type(cmd.substr(5)); //ASCII or BINAR
    } else if (cmd.starts_with("PORT")) {
        handle_port(cmd.substr(5));
    } else if (cmd.starts_with("RETR")) {
        handle_retr(cmd.substr(5)); //transfer from server
    } else if (cmd.starts_with("STOR")) { //save on server
        handle_stor(cmd.substr(5));
    } else {
        send_response("502 Command not implemented.\r\n");
    }
    return true;
}

//save username
void handle_cmd::handle_user(const std::string &userName) {
    this->username = userName;
    send_response("331 Password required.\r\n");
}

//load config and verify pass
void handle_cmd::handle_pass(const std::string &password) {
    load_config("D:/Facultate/ubb-fmi-work/SemestrulV/SS/FTPserver/config.txt");
    if (username == config["user"] && password == config["password"]) {
        authenticated = true;
        send_response("230 User logged in.\r\n");
    } else {
        authenticated = false;
        send_response("530 Login incorrect.\r\n");
    }
}


void handle_cmd::handle_exit() const {
    send_response("221 Goodbye.\r\n");
}


//list files from curr dir
void handle_cmd::handle_list() {
    auto data_socket = INVALID_SOCKET;

    // Setup data connection
    if (active_mode) {
        data_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }

        if (connect(data_socket, (struct sockaddr *) &active_addr, sizeof(active_addr)) == SOCKET_ERROR) {
            send_response("425 Can't establish data connection.\r\n");
            closesocket(data_socket);
            return;
        }

    } else if (passive_socket != INVALID_SOCKET) {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);
        data_socket = accept(passive_socket, (struct sockaddr *) &client_addr, &client_len);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }
    } else {
        send_response("425 Use PASV or PORT first.\r\n");
        return;
    }

    send_response("150 Here comes the directory listing.\r\n");

    //obtin dir curent si il trimit la client
    try {
        std::string listing = get_directory_listing();

        //verific overflow//galben avertisment
        if (listing.size() > static_cast<std::string::size_type>(std::numeric_limits<int>::max())) {
            throw std::overflow_error("Listing size exceeds maximum int value");
        }

        int listing_size = static_cast<int>(listing.size());
        if (send(data_socket, listing.c_str(), listing_size, 0) == SOCKET_ERROR) {
            std::cerr << "[ERROR] Failed to send data: " << WSAGetLastError() << std::endl;
        }
    } catch (const std::exception &e) {
        send_response("450 Requested file action not taken.\r\n");
    }

    closesocket(data_socket);
    send_response("226 Directory send OK.\r\n");
}

//filename and \r\n - for FTP format
std::string handle_cmd::get_directory_listing() {
    std::string listing;
    for (const auto &entry: std::filesystem::directory_iterator(std::filesystem::current_path())) {
        listing += entry.path().filename().string() + "\r\n";
    }
    return listing;
}

void handle_cmd::handle_pasv() {
    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = 0;  // sys alloc free port

    passive_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (passive_socket == INVALID_SOCKET) {
        send_response("425 Error creating passive socket.\r\n");
        return;
    }

    if (bind(passive_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        send_response("425 Error binding passive socket.\r\n");
        closesocket(passive_socket);
        return;
    }

    if (listen(passive_socket, 1) == SOCKET_ERROR) {
        send_response("425 Error listening on passive socket.\r\n");
        closesocket(passive_socket);
        return;
    }

    socklen_t len = sizeof(server_addr);
    getsockname(passive_socket, (struct sockaddr *) &server_addr, &len);

    unsigned short port = ntohs(server_addr.sin_port);  //obtin portul
    unsigned char p1 = port / 256;                     // primul octet
    unsigned char p2 = port % 256;                     // al doilea octet

    char response[128];
    snprintf(response, sizeof(response), "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n", p1, p2);
    send_response(response);

    std::cout << "[DEBUG] Passive mode enabled on port " << port << std::endl;

    closesocket(passive_socket);
    passive_socket = INVALID_SOCKET;
+-
}

//for active mode
void handle_cmd::handle_port(const std::string &params) {
    std::vector<int> parts;
    std::stringstream ss(params);
    std::string part;
    while (std::getline(ss, part, ',')) {
        parts.push_back(std::stoi(part));
    }

    //params in components
    if (parts.size() != 6) {
        send_response("501 Invalid parameters.\r\n");
        return;
    }

    //4 comp. IP, 2 ports
    active_addr.sin_family = AF_INET;
    active_addr.sin_addr.s_addr = htonl((parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3]);
    active_addr.sin_port = htons((parts[4] << 8) | parts[5]);

    active_mode = true;
    send_response("200 PORT command successful.\r\n");
}

//send current dir
//return in FTP format
void handle_cmd::handle_pwd() const {
    char current_dir[PATH_MAX];
    if (getcwd(current_dir, sizeof(current_dir)) != nullptr) {
        char response[PATH_MAX + 50];
        snprintf(response, sizeof(response), "257 \"%s\" is the current directory.\r\n", current_dir);
        send_response(response);
    } else {
        send_response("550 Unable to retrieve current directory.\r\n");
    }
}

//A ASCII I BINAR
void handle_cmd::handle_type(const std::string &type) const {
    if (type == "A") {
        send_response("200 Type set to A.\r\n");
    } else if (type == "I") {
        send_response("200 Type set to I.\r\n");
    } else {
        send_response("504 Command not implemented for that parameter.\r\n");
    }
}

//server -> client
void handle_cmd::handle_retr(const std::string &filePath) {
    auto data_socket = INVALID_SOCKET;

    // setup data connection
    if (active_mode) {
        data_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }

        if (connect(data_socket, (struct sockaddr *) &active_addr, sizeof(active_addr)) == SOCKET_ERROR) {
            send_response("425 Can't establish data connection.\r\n");
            closesocket(data_socket);
            return;
        }

    } else if (passive_socket != INVALID_SOCKET) {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);
        data_socket = accept(passive_socket, (struct sockaddr *) &client_addr, &client_len);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }
    } else {
        send_response("425 Use PASV or PORT first.\r\n");
        return;
    }

    // notific
    send_response("150 Opening data connection.\r\n");

    try {
        // fil reading
        std::ifstream fileStream(filePath, std::ios::binary);
        if (!fileStream.is_open()) {
            send_response("550 File not found.\r\n");
            closesocket(data_socket);
            return;
        }

        char buffer[1024];
        while (fileStream.read(buffer, sizeof(buffer))) {

            //validare de overflow - avertisment

            if (fileStream.gcount() > static_cast<std::streamsize>(std::numeric_limits<int>::max())) {
                throw std::overflow_error("Data size exceeds maximum int value");
            }
            int data_size = static_cast<int>(fileStream.gcount());
            if (send(data_socket, buffer, data_size, 0) == SOCKET_ERROR) {
                std::cerr << "[ERROR] Failed to send data: " << WSAGetLastError() << std::endl;
                break;
            }
        }

        // send data - cea ramasa
        if (fileStream.gcount() > 0) {
            if (fileStream.gcount() > static_cast<std::streamsize>(std::numeric_limits<int>::max())) {
                throw std::overflow_error("Remaining data size exceeds maximum int value");
            }
            int remaining_size = static_cast<int>(fileStream.gcount());
            if (send(data_socket, buffer, remaining_size, 0) == SOCKET_ERROR) {
                std::cerr << "[ERROR] Failed to send remaining data: " << WSAGetLastError() << std::endl;
            }
        }

        fileStream.close();
        send_response("226 Transfer complete.\r\n");
    } catch (const std::exception &e) {
        send_response("450 Requested file action not taken.\r\n");
        std::cerr << "[ERROR] Exception in handle_retr: " << e.what() << std::endl;
    }
    closesocket(data_socket);
}


//client -> server
void handle_cmd::handle_stor(const std::string &filePath) {

    auto data_socket = INVALID_SOCKET;

    // setup data connection
    if (active_mode) {
        data_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }

        if (connect(data_socket, (struct sockaddr *) &active_addr, sizeof(active_addr)) == SOCKET_ERROR) {
            send_response("425 Can't establish data connection.\r\n");
            closesocket(data_socket);
            return;
        }
    } else if (passive_socket != INVALID_SOCKET) {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);
        data_socket = accept(passive_socket, (struct sockaddr *) &client_addr, &client_len);
        if (data_socket == INVALID_SOCKET) {
            send_response("425 Can't open data connection.\r\n");
            return;
        }
    } else {
        send_response("425 Use PASV or PORT first.\r\n");
        return;
    }

    // notific
    send_response("150 Opening data connection.\r\n");

    try {
        // write to file
        std::ofstream fileStream(filePath, std::ios::binary);
        if (!fileStream.is_open()) {
            send_response("550 File unavailable.\r\n");
            closesocket(data_socket);
            return;
        }

        char buffer[1024];
        int bytesRead;
        while ((bytesRead = recv(data_socket, buffer, sizeof(buffer), 0)) > 0) {
            fileStream.write(buffer, bytesRead);
        }

        fileStream.close();
        send_response("226 Transfer complete.\r\n");
    } catch (const std::exception &e) {
        send_response("450 Requested file action not taken.\r\n");
        std::cerr << "[ERROR] Exception in handle_stor: " << e.what() << std::endl;
    }

    closesocket(data_socket);
}