#include "../Sockets/includes/SocketHandler.hpp"

static std::string get_input()
{
    std::string actual_line;
    std::cout << "> ";
    if (!std::getline(std::cin, actual_line, '\n'))
        return "";
    return actual_line;
}

static void transformInput(RType::Utils::MessageParsed_s &modInput, std::string params, RType::Utils::SocketHandler &socket)
{
    if (params == "connect") {
        modInput.msgType = 21;
        modInput.bytes[0] = 1;
        socket.send(modInput);
        return;
    }
    if (params == "cteam") {
        modInput.msgType = 23;
        modInput.bytes[0] = 1;
        socket.send(modInput);
        return;
    }
    // if (params ==)
}

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
    for (int i = 0; i < 7; ++i)
        toSend.bytes[i] = 0;
    std::string actualLine = get_input();
    while (actualLine != "") {
        transformInput(toSend, actualLine, handler);
        actualLine = get_input();
    }

    return 0;
}