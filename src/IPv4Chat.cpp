#include "IPv4Chat.hpp"

const char* BROADCAST_IP = "255.255.255.255";
const int MAX_MESSAGE_SIZE = 1007;

IPv4Chat::IPv4Chat(std::string IP ,int PORT) : sock_(-1) {
    IPv4Chat::IP = IP;
    IPv4Chat::PORT = PORT;
    memset(&recvAddr_, 0, sizeof(recvAddr_));

    recvAddr_.sin_family = AF_INET;
    recvAddr_.sin_port = htons(PORT);
    recvAddr_.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(&broadcastAddr, 0, sizeof(broadcastAddr));

    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_port = htons(PORT);
    recvAddr_.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    inet_pton(AF_INET, BROADCAST_IP, &broadcastAddr.sin_addr);
}

IPv4Chat::~IPv4Chat() {
    if (sock_ != -1) {
        close(sock_);
    }
}

bool IPv4Chat::initializeSocket() {
    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_ == -1) {
        std::cerr << "Error: Could not create socket\n";
        return false;
    }

    if (bind(sock_, (sockaddr*)&recvAddr_, sizeof(recvAddr_)) == -1) {
        std::cerr << "Error: Bind failed\n";
        close(sock_);
        return false;
    }

    int broadcastPermission = 1;
    if (setsockopt(sock_, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission)) == -1){
        std::cerr << "Error: Setsock failed\n";
        close(sock_);
        return false;
    }

    return true;
}

void IPv4Chat::receive() {
    char buffer[MAX_MESSAGE_SIZE];
    sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);
    while (true) {
        int bytesRecv = recvfrom(sock_, buffer, sizeof(buffer), 0,
                                    (sockaddr*)&senderAddr, &senderLen);
        if (bytesRecv == -1) {
            std::cerr << "Error: Failed to receive message\n";
            continue;
        }

        std::string address = inet_ntoa(senderAddr.sin_addr);

        if (IP == address){
            continue;
        }

        buffer[bytesRecv] = '\0';
        std::cout << "Received message from " << inet_ntoa(senderAddr.sin_addr) << ": " << buffer << std::endl;
    }
}


void IPv4Chat::send(const std::string& message) {
    if (sendto(sock_, message.c_str(), message.length(), 0,
               (sockaddr*)&broadcastAddr, sizeof(broadcastAddr)) == -1) {
        std::cerr << "Error: Failed to send message\n";
    }
}
