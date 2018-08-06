#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "view.cpp"

View view;
int main() {
    int client;
    int portNum = 1500;
    int bufsize = 1024;
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
        std::cout << "Send message to server: ";
        std::string responseString = "";
        char response[bufsize];
        getline(std::cin, responseString);
        strcpy (response, responseString.c_str());
        send(client, response, bufsize, 0);
        if (responseString == "exit") {
            break;
        }
        
        recv(client, buffer, bufsize, 0);
        std::string serverResponse = buffer;   
        if (serverResponse == "exit") {
            break;
        }

        std::cout << "Received: " << serverResponse << std::endl;
    }

    view.goodbye();
    close(client);
    
    return 0;
}