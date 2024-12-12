#ifndef HANDLE_CMD_H
#define HANDLE_CMD_H

#include <string>
#define BUFFER_SIZE 1024


#include <fstream>
#include <map>

class handle_cmd {
public:
    explicit handle_cmd(SOCKET client_socket);
    ~handle_cmd();

    bool process_command(const std::string &cmd);
    void send_response(const char *response) const;

private:
//    std::map<std::string, std::string> config; //for data auth
    SOCKET client_socket;
    unsigned long long passive_socket = -1;
    sockaddr_in active_addr; // addr for active mode
    bool active_mode = false;

    bool authenticated = false; // status of auth
    std::string username;       // stochez username for password check

    static void load_config(const std::string &file_name);
    void handle_user(const std::string &userName);
    void handle_pass(const std::string &password);
    void handle_exit() const;
    void handle_list();
    void handle_retr(const std::string &filename);
    void handle_stor(const std::string &filename);
    void handle_pwd() const;
    void handle_type(const std::string &type) const;
    void handle_pasv();
    void handle_port(const std::string &params);
    static std::string get_directory_listing();

};

#endif // HANDLE_CMD_H
