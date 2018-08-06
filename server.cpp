#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "view.cpp"

void loop_listen(int serverSocket, int bufsize, struct sockaddr_in server_addr) {
    char buffer[bufsize];
    strcpy(buffer, "Server connected");
    send(serverSocket, buffer, bufsize, 0);

    while (true) {
        recv(serverSocket, buffer, bufsize, 0);
        std::string clientResponse = buffer;
        if(clientResponse == "exit") { // As this is only 1 to 1 Server/Client, it will stop when the serverSocket disconects.
            break;
        }
        std::cout << "Client sent: " << buffer << std::endl;

        std::cout << "Response: ";
        std::string responseString = "";
        char response[bufsize];
        getline(std::cin, responseString);
        strcpy (response, responseString.c_str());

        send(serverSocket, response, bufsize, 0);
        if (responseString == "exit") {
            break;
        }
    }
}

View view;
int main() {

    int serverSocket;
    int portNum = 1500;
    int bufsize = 1024;

    struct sockaddr_in server_addr;
    socklen_t size;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        view.socket_creation_failure("Server");
        exit(1);
    }

    view.socket_creation_success("Server");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    int bindResponse = bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bindResponse == -1) {
        view.bind_failure();
        exit(1);
    }

    view.listening_clients();
    listen(serverSocket, 1);

    size = sizeof(server_addr);
    serverSocket = accept(serverSocket, (struct sockaddr *)&server_addr, &size);

    view.conection_received();

    if (serverSocket == -1) 
        exit(1);

    loop_listen(serverSocket, bufsize, server_addr);

    view.server_goodbye(inet_ntoa(server_addr.sin_addr));
    close(serverSocket);

    return 0;
}