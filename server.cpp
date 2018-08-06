#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "view.cpp"
#include "utils.cpp"

View view;
Utils utils;
void connection_in_progress(int serverSocket, int bufsize, struct sockaddr_in server_addr) {
    char buffer[bufsize];
    strcpy(buffer, "Server connected");
    send(serverSocket, buffer, bufsize, 0);

    while (true) {
        recv(serverSocket, buffer, bufsize, 0);
        std::string clientResponse = buffer;
        if(clientResponse == "exit") { // As this is only 1 to 1 Server/Client, it will stop when the serverSocket disconects.
            break;
        }
        view.received("Client sent: ", clientResponse);

        view.send_message("Client");
        std::string responseString = "";
        char response[bufsize];
        getline(std::cin, responseString);
        strcpy (response, responseString.c_str());

        std::string messageToLog = utils.create_log_format(responseString);
        utils.save_to_file("server.log", messageToLog); // Saving response to server.log file
        send(serverSocket, response, bufsize, 0);
        if (responseString == "exit") {
            break;
        }
    }
}

int main() {
    int serverSocket;
    int portNum;
    int bufsize;
    std::ifstream infile("sis.config");
    std::string line;
    while (std::getline(infile, line)) {
        std::size_t foundPortNum = line.find("portNum");
        if (foundPortNum != std::string::npos) {
            portNum = std::stoi(line.substr(8));
        }                    
        
        std::size_t foundBufSize = line.find("bufSize");
        if (foundBufSize != std::string::npos)
            bufsize = std::stoi(line.substr(8));
    }

    struct sockaddr_in server_addr;
    socklen_t socketSize;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        view.socket_creation_failure("Server");
        exit(1);
    }

    view.socket_creation_success("Server");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);
    socketSize = sizeof(server_addr);

    int bindResponse = bind(serverSocket, (struct sockaddr*)&server_addr, socketSize);
    if (bindResponse == -1) {
        view.bind_failure();
        exit(1);
    }

    view.listening_clients();
    listen(serverSocket, 1);

    serverSocket = accept(serverSocket, (struct sockaddr *)&server_addr, &socketSize);

    view.conection_received();

    if (serverSocket == -1) 
        exit(1);

    connection_in_progress(serverSocket, bufsize, server_addr);

    view.server_goodbye(inet_ntoa(server_addr.sin_addr));
    close(serverSocket);

    return 0;
}