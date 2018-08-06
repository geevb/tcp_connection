#include <iostream>
#include <string.h>

class View  {
    public:
    void socket_creation_failure(std::string side) {
        std::cout << "Error creating " + side + " socket." << std::endl;
    }

    void socket_creation_success(std::string side) {
        std::cout << side + " socket successfully created." << std::endl;
    }

    void bind_failure() {
        std::cout << "Bind failed." << std::endl;
    }

    void listening_clients() {
        std::cout << "Listening for clients..." << std::endl;
    }

    void conection_received() {
        std::cout << "Client connected!" << std::endl;
    }

    void end_connection_tip() {
        std::cout << "Type 'exit' to stop the connection" << std::endl;
    }

    void goodbye() {
        std::cout << "Thanks for using, goodbye!" << std::endl;
    }

    void connecting_to_port(int portNumber) {
        std::cout << "Connection to the server port number: " << portNumber << std::endl;
    }

    void server_goodbye(std::string ip) {
        std::cout << "IP " << ip << " ended the connection. Goodbye!" << std::endl;
    }

    void waiting_server_confirmation() {
        std::cout << "Waiting the server's confirmation" << std::endl;
    }
    
    void server_connection_success() {
        std::cout << "Successfully connected!" << std::endl;
    }

    void received(std::string side, std::string response) {
        std::cout << side << response << std::endl;
    }

    void send_message(std::string side) {
        std::cout << "Send message to " << side << ": ";
    }
};
