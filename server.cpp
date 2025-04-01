#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <fstream>
#include <string>

#include "Thermostat.h"
#include "Lights.h"
#include "Speaker.h"





#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

// ---- SMART HOME SYSTEM --------------------------------------------
// 
//create an array of lights
int NUM_LIGHTS = 10;
int NUM_THERMOSTAT = 1;
int NUM_SPEAKERS = 4;

Lights lightsArray[10] = { Lights(false), Lights(false), Lights(false), Lights(false),
                     Lights(false), Lights(false), Lights(false), Lights(false),
                     Lights(false), Lights(false) };
Thermostat thermostatArray[1] = { Thermostat(20, false) };
Speaker speakerArray[4] = { Speaker(50, false),Speaker(50, false) ,Speaker(50, false) ,Speaker(50, false) };


void handleClient(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE] = { 0 };

    // Receive message from the client
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        std::cerr << "Error receiving data from client" << std::endl;
        closesocket(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0'; // Null-terminate the buffer
    std::cout << "Received: " << buffer << std::endl;
    

    std::string request(buffer);

    //process GET requests
    if (request.substr(0, 3) == "GET") {
        std::string path = request.substr(4); //Everything after GET

        //process till first '/'
        size_t pos = path.find('/');
        std::string device = path.substr(0, pos);
        std::cout << "DEVICE IS: " << device;
        int index = -1;

        if (pos != std::string::npos) { // Ensure '/' was found
            path = path.substr(pos + 1); // Extract the portion after '/'
            pos = path.find('/');
            std::string indexStr = path.substr(0, pos);
            index = std::stoi(indexStr); // Convert to int
            std::cout << "Index is: " << index << std::endl;
        }
        //DEVICE AND INDEX IS FOUND:
        if (device == "lights") {
            //check if index is out of scope
            if (index < NUM_LIGHTS && index >= 0) {
                //check if there are more commands after, else just return status of light
                path = path.substr(pos + 1);
                pos = path.find('/');

                //if there was another '/' after the index
                if (pos != std::string::npos) {
                    std::string command = path.substr(0, pos);
                    if (command == "switch") {
                        lightsArray[index].changeState();
                        std::string response = "Light " + std::to_string(index) + " has been turned " + (lightsArray[index].getState() ? "on\n" : "off\n");
                        send(clientSocket, response.c_str(), response.length(), 0);
                    }
                }
                else {
                    std::string response = "Light " + std::to_string(index) + " is " + (lightsArray[index].getState() ? "on\n" : "off\n");
                    send(clientSocket, response.c_str(), response.length(), 0);
                }
            }
            else {
                std::string response = "INDEX IS OUT OF SCOPE";
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }
        else if (device == "speakers") {
            //check if index is out of scope
            if (index < NUM_SPEAKERS && index >= 0) {
                //check if there are more commands after, else just return status of light
                path = path.substr(pos + 1);
                pos = path.find('/');

                //if there was another '/' after the index
                if (pos != std::string::npos) {
                    std::string command = path.substr(0, pos);
                    if (command == "switch") {
                        speakerArray[index].switchButton();
                        std::string response = "Speaker " + std::to_string(index) + " has been turned " + (speakerArray[index].getState() ? "on\n" : "off\n");
                        send(clientSocket, response.c_str(), response.length(), 0);
                    }
                    else if (command == "setVolume") {
                        path = path.substr(pos + 1);
                        pos = path.find('/');
                        if (pos != std::string::npos) {
                            int vol = std::stoi(path.substr(0, pos));
                            speakerArray[index].setVolume(vol);
                            std::string response = "Speaker " + std::to_string(index) + " volume has been set to " + std::to_string(vol) + "\n";
                            send(clientSocket, response.c_str(), response.length(), 0);
                        }
                    }
                }
                else {
                    std::string response = "Speaker " + std::to_string(index) + " is " + (speakerArray[index].getState() ? "on\n" : "off\n");
                    send(clientSocket, response.c_str(), response.length(), 0);
                }
            }
            else {
                std::string response = "INDEX IS OUT OF SCOPE";
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }
        else if (device == "thermostats") {
            //check if index is out of scope
            if (index < NUM_THERMOSTAT && index >= 0) {
                //check if there are more commands after, else just return status of light
                path = path.substr(pos + 1);
                pos = path.find('/');

                //if there was another '/' after the index
                if (pos != std::string::npos) {
                    std::string command = path.substr(0, pos);
                    if (command == "switch") {
                        thermostatArray[index].switchButton();
                        std::string response = "Thermostat " + std::to_string(index) + " has been turned " + (thermostatArray[index].getState() ? "on" : "off") + ", temperature is " + std::to_string(thermostatArray[index].getTemperature()) + "C\n";
                        send(clientSocket, response.c_str(), response.length(), 0);
                    }
                    else if (command == "setTemp") {
                        path = path.substr(pos + 1);
                        pos = path.find('/');
                        if (pos != std::string::npos) {
                            float temp = std::stof(path.substr(0, pos));
                            thermostatArray[index].setTemperature(temp);
                            std::string response = "Thermostat " + std::to_string(index) + " volume has been set to " + std::to_string(temp) + "\n";
                            send(clientSocket, response.c_str(), response.length(), 0);
                        }
                    }
                }
                else {
                    std::string response = "Thermostat " + std::to_string(index) + " is " + (thermostatArray[index].getState() ? "on" : "off") + ", at temperature " + std::to_string(thermostatArray[index].getTemperature()) + "C\n";
                    send(clientSocket, response.c_str(), response.length(), 0);
                }
            }
            else {
                std::string response = "INDEX IS OUT OF SCOPE";
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }



    }



    if (std::string(buffer) == "start") {
        std::ifstream file("test.txt");
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                send(clientSocket, line.c_str(), line.length(), 0);
                send(clientSocket, "\n", 1, 0);
            }
        }
        else {
            std::string error = "Error opening file\n";
            send(clientSocket, error.c_str(), error.length(), 0);
        }
    }

    // Close the client socket
    closesocket(clientSocket);
}

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Binding failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept client" << std::endl;
            continue; // Continue accepting new clients
        }

        // Spawn a new thread for each client
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach(); // Detach the thread to run independently
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}