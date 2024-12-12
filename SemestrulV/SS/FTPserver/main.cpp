#include <iostream>
#include "server.h"

int main() {
    server server;

    //port 21 - port standard FTP
    if (!server.start(21)) {
        std::cerr << "Eroare pornire server\n";
        return 1;
    }

    std::cout << "Portul 21...\n";
    server.run();
    server.stop();

    return 0;
}
