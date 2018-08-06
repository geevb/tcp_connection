#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "view.cpp"
#include "utils.cpp"

View view;
Utils utils;
int main() {
    int client;

    std::ifstream infile("sis.config");
    std::string line;
    int portNum;
    int bufsize;
    while (std::getline(infile, line)) {
        std::size_t foundPortNum = line.find("portNum");
        if (foundPortNum != std::string::npos)
            portNum = std::stoi(line.substr(8));            
        
        std::size_t foundBufSize = line.find("bufSize");
        if (foundBufSize != std::string::npos)
            bufsize = std::stoi(line.substr(8));
    }
    
    char buffer[bufsize];
    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        view.socket_creation_failure("Client");
        exit(1);
    }   

    view.socket_creation_success("Client");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    int connectionResponse = connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connectionResponse == 0)
        view.connecting_to_port(portNum);

    view.waiting_server_confirmation();
    recv(client, buffer, bufsize, 0);

    view.server_connection_success();
    view.end_connection_tip();

    while(true) {
        view.send_message("Server");
        std::string responseString = "";
        char response[bufsize];
        getline(std::cin, responseString);
        strcpy (response, responseString.c_str());
        send(client, response, bufsize, 0);
        
        std::string messageToLog = utils.create_log_format(responseString);
        utils.save_to_file("client.log", messageToLog);
        if (responseString == "exit") {
            break;
        }
        
        recv(client, buffer, bufsize, 0);
        std::string serverResponse = buffer;   
        if (serverResponse == "exit") {
            break;
        }

        view.received("Server responded: ", serverResponse);
    }

    view.goodbye();
    close(client);
    
    return 0;
}