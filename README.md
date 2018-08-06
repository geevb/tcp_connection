# TCPConnection

Designed as an example of a simple socket connection through TCP.
This project was developed and tested using Ubuntu 16.04 LTS.


## Getting Started

* This project was developed exclusively using C++
* To make use of it, clone/download this repository
* The data will be stored in files called `client.log` and `server.log`. 


### Prerequisites

 * G++ Compiler
 * Linux Enviroment(Preferably Ubuntu 16.04)


### Installing

* The first step will be cloning or downloading this repository.

* Then configurate the file `sis.config` inside the config folder accordingly to the port number or buffer size as:
```
portNum=desiredPortNumber(int)
bufSize=desiredBufferSize(int)
```

* Compile both the client.cpp and server.cpp with the following command
    * `g++ -std=c++11 -o server server.cpp`
    * `g++ -std=c++11 -o client client.cpp`
* Execute the server file with `./server`
* Then, execute the client file with `./client`


## Authors
* **Getúlio Vieira Benincá**
