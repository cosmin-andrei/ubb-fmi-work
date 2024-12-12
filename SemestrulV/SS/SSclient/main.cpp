#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

class FTPClient {
private:
    SOCKET control_socket;
    bool is_connected;
    bool is_logged_in;
    char buffer[1024];

    void trim(std::string& str) {
        while (!str.empty() && std::isspace(str.front())) {
            str.erase(str.begin());
        }
        while (!str.empty() && std::isspace(str.back())) {
            str.pop_back();
        }
    }

    std::string receive_response() {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(control_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            throw std::runtime_error("Connection error");
        }
        std::string response(buffer);
        trim(response);
        std::cout << "Server Response: " << response << std::endl;
        return response;
    }

    void send_command(const std::string& cmd) {
        std::string full_cmd = cmd + "\r\n";
        if (send(control_socket, full_cmd.c_str(), full_cmd.length(), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Send failed");
        }
    }

    SOCKET create_data_connection(bool passive) {
        if (passive) {
            // Implement passive mode connection
            send_command("PASV");
            std::string pasv_response = receive_response();

            // Parse PASV response
            size_t start = pasv_response.find('(');
            size_t end = pasv_response.find(')', start);
            if (start == std::string::npos || end == std::string::npos) {
                throw std::runtime_error("Invalid PASV response");
            }

            std::string pasv_info = pasv_response.substr(start + 1, end - start - 1);
            std::vector<int> parts;
            std::stringstream ss(pasv_info);
            std::string part;

            while (std::getline(ss, part, ',')) {
                parts.push_back(std::stoi(part));
            }

            // Construct server address
            char server_ip[64];
            sprintf_s(server_ip, "%d.%d.%d.%d", parts[0], parts[1], parts[2], parts[3]);
            int port = (parts[4] * 256) + parts[5];

            // Create socket
            SOCKET data_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (data_socket == INVALID_SOCKET) {
                throw std::runtime_error("Could not create data socket");
            }

            sockaddr_in server_addr = {};
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);
            inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

            if (::connect(data_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
                closesocket(data_socket);
                throw std::runtime_error("Could not connect to data socket");
            }

            return data_socket;
        }

        // Active mode (not fully implemented in this version)
        throw std::runtime_error("Active mode not yet implemented");
    }

public:
    FTPClient() : control_socket(INVALID_SOCKET), is_connected(false), is_logged_in(false) {
        // Initialize Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }
    }

    ~FTPClient() {
        if (is_connected) {
            disconnect();
        }
        WSACleanup();
    }

    void connect(const std::string& server, int port) {
        // Create socket
        control_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (control_socket == INVALID_SOCKET) {
            throw std::runtime_error("Could not create socket");
        }

        // Set up server address
        sockaddr_in server_addr = {};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, server.c_str(), &server_addr.sin_addr);

        // Connect to server
        if (::connect(control_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
            closesocket(control_socket);
            throw std::runtime_error("Could not connect to server");
        }

        // Receive welcome message
        receive_response();
        is_connected = true;
    }

    void login(const std::string& username, const std::string& password) {
        if (!is_connected) {
            throw std::runtime_error("Not connected to server");
        }

        // Send username
        send_command("USER " + username);
        receive_response();

        // Send password
        send_command("PASS " + password);
        std::string login_response = receive_response();

        // Check if login was successful
        is_logged_in = (login_response.find("230") != std::string::npos);
        if (!is_logged_in) {
            throw std::runtime_error("Login failed");
        }
    }

    void list_files() {
        if (!is_logged_in) {
            throw std::runtime_error("Not logged in");
        }

        // Create data connection in passive mode
        SOCKET data_socket = create_data_connection(true);

        // Send LIST command
        send_command("LIST");
        receive_response(); // Receive initial response

        // Receive file listing
        char list_buffer[4096];
        int bytes_received;
        while ((bytes_received = recv(data_socket, list_buffer, sizeof(list_buffer) - 1, 0)) > 0) {
            list_buffer[bytes_received] = '\0';
            std::cout << list_buffer;
        }

        closesocket(data_socket);
        receive_response(); // Receive transfer complete response
    }

    void download_file(const std::string& remote_filename, const std::string& local_filename) {
        if (!is_logged_in) {
            throw std::runtime_error("Not logged in");
        }

        // Create data connection in passive mode
        SOCKET data_socket = create_data_connection(true);

        // Set binary transfer mode
        send_command("TYPE I");
        receive_response();

        // Initiate file download
        send_command("RETR " + remote_filename);
        receive_response(); // Initial response

        // Open local file for writing
        std::ofstream local_file(local_filename, std::ios::binary);
        if (!local_file) {
            closesocket(data_socket);
            throw std::runtime_error("Could not create local file");
        }

        // Receive file data
        char file_buffer[4096];
        int bytes_received;
        while ((bytes_received = recv(data_socket, file_buffer, sizeof(file_buffer), 0)) > 0) {
            local_file.write(file_buffer, bytes_received);
        }

        local_file.close();
        closesocket(data_socket);
        receive_response(); // Transfer complete response
    }

    void upload_file(const std::string& local_filename, const std::string& remote_filename) {
        if (!is_logged_in) {
            throw std::runtime_error("Not logged in");
        }

        // Create data connection in passive mode
        SOCKET data_socket = create_data_connection(true);

        // Set binary transfer mode
        send_command("TYPE I");
        receive_response();

        // Initiate file upload
        send_command("STOR " + remote_filename);
        receive_response(); // Initial response

        // Open local file for reading
        std::ifstream local_file(local_filename, std::ios::binary);
        if (!local_file) {
            closesocket(data_socket);
            throw std::runtime_error("Could not open local file");
        }

        // Send file data
        char file_buffer[4096];
        while (local_file.read(file_buffer, sizeof(file_buffer))) {
            send(data_socket, file_buffer, local_file.gcount(), 0);
        }

        // Send any remaining data
        if (local_file.gcount() > 0) {
            send(data_socket, file_buffer, local_file.gcount(), 0);
        }

        local_file.close();
        closesocket(data_socket);
        receive_response(); // Transfer complete response
    }

    void disconnect() {
        if (is_connected) {
            send_command("QUIT");
            receive_response();
            closesocket(control_socket);
            is_connected = false;
            is_logged_in = false;
        }
    }
};

int main() {
    try {
        FTPClient client;

        // Connect to the server
        client.connect("127.0.0.1", 21);

        // Login with hardcoded credentials
        client.login("user", "password");

        // Demonstrate different operations
        std::cout << "Listing files:\n";
        client.list_files();

        // Uncomment and modify as needed
        client.upload_file("local_file.txt", "test.txt");
        client.download_file("test.txt", "test.txt");


        // Disconnect
        client.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}