#include "../Sockets/includes/SocketHandler.hpp"
#include <thread>
#include "../server/includes/ComCodes.hpp"

static std::string get_input()
{
    std::string actual_line;
    std::cout << "> ";
    if (!std::getline(std::cin, actual_line, '\n'))
        return "";
    return actual_line;
}

static void transformInput(RType::Utils::MessageParsed_s &modInput, std::string params, RType::Utils::SocketHandler &socket, int port)
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
    if (params == "msg") {
        std::cout << "msg is sended" << std::endl;
        int tmpPort = modInput.senderPort;
        modInput.senderPort = 4000;
        modInput.msgType = 11;
        socket.send(modInput);
        modInput.senderPort = tmpPort;
        return;
    }
    if (params == "list") {
        modInput.msgType = 25;
        socket.send(modInput);
        return;
    }
    if (params == "deco") {
        modInput.msgType = 22;
        modInput.bytes[0] = 1;
        socket.send(modInput);
        return;
    }
}

static void threadFn(std::shared_ptr<RType::Utils::SocketHandler> socket, bool &toStop)
{
    while (!toStop) {
        RType::Utils::MessageParsed_s msg = socket->receive();
        std::cout << "Receive with status " << static_cast<int>(msg.msgType) << std::endl; 
    }
}


int main(int av, char **ar)
{
    if (av != 2)
        return 1;
    std::srand(std::time(nullptr));
    int port = 4242 + std::rand() % 1000;
    bool toStop = false;
    RType::Utils::SocketHandler handler("127.0.0.1", port);
    RType::Utils::MessageParsed_s toSend;
    std::thread newThread(threadFn, handler.getInstance(), std::ref(toStop));
    toSend.msgType = static_cast<unsigned char>(std::atoi(ar[1]));
    toSend.senderIp = "127.0.0.1";
    toSend.senderPort = 4000;
    for (int i = 0; i < 7; ++i)
        toSend.bytes[i] = 0;
    std::string actualLine = get_input();
    while (actualLine != "") {
        transformInput(toSend, actualLine, handler, port);
        actualLine = get_input();
    }
    toStop = true;
    transformInput(toSend, "deco", handler, port);
    newThread.join();
    return 0;
}