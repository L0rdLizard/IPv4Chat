#include <iostream>
#include <pthread.h>
#include "IPv4Chat.hpp"

const int MAX_MESSAGE_SIZE = 1007;

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
    std::cin.ignore(); 
    while (true) {
        std::string message;
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
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <PORT>\n";
        return 1;
    }

    IPv4Chat chat(argv[1] , std::atoi(argv[2]));
    if (!chat.initializeSocket()) {
        return 1;
    }

    pthread_t receiverThreadId, senderThreadId;
    pthread_create(&receiverThreadId, nullptr, receiverThread, &chat);
    pthread_create(&senderThreadId, nullptr, senderThread, &chat);

    pthread_join(receiverThreadId, nullptr);
    pthread_join(senderThreadId, nullptr);

    return 0;
}
