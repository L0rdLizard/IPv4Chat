#ifndef IPV4CHAT_HPP
#define IPV4CHAT_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class IPv4Chat {
private:
    std::string IP;
    int PORT;
    int sock_;
    sockaddr_in recvAddr_;
    sockaddr_in broadcastAddr;

public:
    IPv4Chat(std::string IP ,int PORT);
    ~IPv4Chat();
    bool initializeSocket();
    void receive();
    void send(const std::string& message);
};

#endif /* IPV4CHAT_HPP */
