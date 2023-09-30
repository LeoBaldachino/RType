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

std::vector<std::string> parseString(const std::string &str, char parseTo)
{
    int actual = 0;
    std::vector<std::string> parsed;
    parsed.push_back(std::string(""));
    for (auto i = 0; i < str.size(); ++i) {
        if (str[i] != parseTo)
            parsed[actual].push_back(str[i]);
        else {
            actual++;
            parsed.push_back(std::string(""));
        }
    }
    return parsed;
}

static void displayTeam(const RType::Utils::MessageParsed_s &msg)
{
    std::cout << "Team id = " << static_cast<int>(msg.bytes[0]) << " Users " << static_cast<int>(msg.bytes[1]) << " / " << static_cast<int>(msg.bytes[2]) << std::endl;
}

static void transformInput(RType::Utils::MessageParsed_s &modInput, const std::string &param, RType::Utils::SocketHandler &socket, int port)
{
    if (param == "")
        return;
    std::vector<std::string> params = parseString(param, ' ');
    std::cout << "Message send..." << std::endl;
    if (params[0] == "connect") {
        modInput.msgType = 21;
        modInput.bytes[0] = std::stoi(params[1]);
        socket.send(modInput);
        return;
    }
    if (params[0] == "cteam") {
        modInput.msgType = 23;
        modInput.bytes[0] = std::stoi(params[1]);;
        socket.send(modInput);
        return;
    }
    if (params[0] == "msg") {
        std::cout << "msg is sended" << std::endl;
        int tmpPort = modInput.senderPort;
        modInput.senderPort = 4000;
        modInput.msgType = 11;
        socket.send(modInput);
        modInput.senderPort = tmpPort;
        return;
    }
    if (params[0] == "list") {
        modInput.msgType = 25;
        socket.send(modInput);
        return;
    }
    if (params[0] == "deco") {
        modInput.msgType = 22;
        modInput.bytes[0] = std::stoi(params[1]);
        socket.send(modInput);
        return;
    }
}

static void threadFn(std::shared_ptr<RType::Utils::SocketHandler> socket, bool &toStop)
{
    while (!toStop) {
        RType::Utils::MessageParsed_s msg = socket->receive();
        std::cout << "Receive with status " << static_cast<int>(msg.msgType) << std::endl;
        if (msg.msgType == 24)
            displayTeam(msg);
        if (msg.msgType == 27) {
            std::cout << "Send ping msg" << std::endl;
            msg.senderIp = "127.0.0.1";
            msg.senderPort = 4000;
            socket->send(msg);
        }
        if (msg.msgType == 32)
            toStop = true;
    }
}


int main(int av, char **ar)
{
    std::srand(std::time(nullptr));
    // unsigned short random = static_cast<unsigned short>(std::rand() % 65000);
    // RType::Utils::MessageParsed_s toSend;
    // toSend.setFirstShort(random);
    // std::cout << "Short decoded is " << toSend.getFirstShort() << " Short sended is " << random << std::endl;
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
    while (actualLine != "" && !toStop) {
        transformInput(toSend, actualLine, handler, port);
        actualLine = get_input();
    }
    toStop = true;
    // transformInput(toSend, "deco", handler, port);
    newThread.join();
    return 0;
}