#include "ServerPersistence.h"
#include <stdio.h>
#include <iostream>
/*#include <socketapi.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")*/
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "HTTPRequest.hpp"

ServerPersistence::ServerPersistence(ISerializer* serializer, const std::string& address, uint32_t port) : IPersistence(serializer)
{
    this->address = address;
    this->port = port;
    initialized = false;
}

ServerPersistence::~ServerPersistence()
{
    closesocket(fdSock);
}

bool ServerPersistence::Open()
{
    bool result = true;
    try 
    {
        http::Request request(address + ":" + std::to_string(port) + "/tracker");
        const auto response = request.send("GET", "", {}, std::chrono::milliseconds{ 1000 });

        std::cout << "Server reached\n"; // print the result
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Cannot reach server\n";
        std::cerr << "Request failed, error: " << e.what() << '\n';
        result = false;
    }
    
    return initialized = result;
}

void ServerPersistence::Send(const TrackerEvent& evt)
{
    if (!initialized) return;
    eventQueue.push(evt);
}

void ServerPersistence::Flush()
{
    if (!initialized) return;

    while (!eventQueue.empty())
    {
        TrackerEvent evt = eventQueue.front(); eventQueue.pop();
        std::string str = serializer->Serialize(evt);
        
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

        // Post request to server
        try
        {
            http::Request request(address + ":" + std::to_string(port) + "/tracker");

            const auto response = request.send("POST", str, {
                "Content-Type: text/plain"
                }, std::chrono::milliseconds{ 1000 });

            std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        }
        catch (const std::exception& e)
        {
            std::cerr << "Cannot reach server\n";
            std::cerr << "Request failed, error: " << e.what() << '\n';
        }
    }

}
