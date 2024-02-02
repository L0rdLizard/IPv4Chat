#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>


// const char* BROADCAST_IP = "255.255.255.255"; // Широковещательный адрес IPv4
const char* BROADCAST_IP = "127.0.0.1"; // Широковещательный адрес IPv4
const int MAX_MESSAGE_SIZE = 1007;

class IPv4Chat {
private:
    int PORT;
    int sock_;
    sockaddr_in recvAddr_;

public:
    IPv4Chat(int PORT) : sock_(-1) {
        IPv4Chat::PORT = PORT;
        memset(&recvAddr_, 0, sizeof(recvAddr_));
        recvAddr_.sin_family = AF_INET;
        recvAddr_.sin_port = htons(PORT);
        recvAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    ~IPv4Chat() {
        if (sock_ != -1) {
            close(sock_);
        }
    }

    bool initializeReceiver() {
        sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock_ == -1) {
            std::cerr << "Error: Could not create socket\n";
            return false;
        }

        // sockaddr_in recvAddr__;

        // memset(&recvAddr__, 0, sizeof(recvAddr__));
        // recvAddr__.sin_family = AF_INET;
        // recvAddr__.sin_port = htons(8888);
        // recvAddr__.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sock_, (sockaddr*)&recvAddr_, sizeof(recvAddr_)) == -1) {
            std::cerr << "Error: Bind failed\n";
            close(sock_);
            return false;
        }

        return true;
    }

    void receive() {
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
            buffer[bytesRecv] = '\0';
            std::cout << "Received message from " << inet_ntoa(senderAddr.sin_addr) << ": " << buffer << std::endl;
        }
    }

    void send(const std::string& message) {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock == -1) {
            std::cerr << "Error: Could not create socket\n";
            return;
        }

        sockaddr_in broadcastAddr;
        memset(&broadcastAddr, 0, sizeof(broadcastAddr));
        broadcastAddr.sin_family = AF_INET;
        // broadcastAddr.sin_port = htons(PORT);
        broadcastAddr.sin_port = htons(8888);
        inet_pton(AF_INET, BROADCAST_IP, &broadcastAddr.sin_addr);

        if (sendto(sock, message.c_str(), message.length(), 0,
                   (sockaddr*)&broadcastAddr, sizeof(broadcastAddr)) == -1) {
            std::cerr << "Error: Failed to send message\n";
        }

        close(sock);
    }
};

void* receiverThread(void* arg) {
    IPv4Chat* chat = static_cast<IPv4Chat*>(arg);
    chat->receive();
    return nullptr;
}

void* senderThread(void* arg) {
    IPv4Chat* chat = static_cast<IPv4Chat*>(arg);
    std::string nickname;
    std::cout << "Enter your nickname: ";
    std::cin >> nickname;
    std::cin.ignore(); // Clear input buffer
    while (true) {
        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);
        if (message.empty()) {
            std::cerr << "Error: Message cannot be empty\n";
            continue;
        }
        std::string fullMessage = nickname + ": " + message;
        if (fullMessage.size() > MAX_MESSAGE_SIZE) {
            std::cerr << "Error: Message too long\n";
            continue;
        }
        chat->send(fullMessage);
    }
    return nullptr;
}

int main(int argc, char const* argv[]) {
    IPv4Chat chat(std::atoi(argv[1]));
    if (!chat.initializeReceiver()) {
        return 1;
    }

    pthread_t receiverThreadId, senderThreadId;
    pthread_create(&receiverThreadId, nullptr, receiverThread, &chat);
    pthread_create(&senderThreadId, nullptr, senderThread, &chat);

    pthread_join(receiverThreadId, nullptr);
    pthread_join(senderThreadId, nullptr);

    return 0;
}
