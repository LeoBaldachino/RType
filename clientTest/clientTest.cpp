#include "../Sockets/includes/SocketHandler.hpp"


int main(int av, char **ar)
{
    if (av != 2)
        return 1;
    std::srand(std::time(nullptr));
    RType::Utils::SocketHandler handler("127.0.0.1", 4242 + std::rand() % 1000);
    RType::Utils::MessageParsed_s toSend;
    toSend.msgType = static_cast<unsigned char>(std::atoi(ar[1]));
    toSend.senderIp = "127.0.0.1";
    toSend.senderPort = 4000;
    for (int i = 0; i < 7; ++i) {
        unsigned char value = static_cast<unsigned char>(std::rand() % 254);
        std::printf("Value %d = %d\n", i , value);
        toSend.bytes[i] = value;
    }
    handler.send(toSend);
    return 0;
}