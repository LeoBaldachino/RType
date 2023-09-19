// #define IP "127.0.0.1"
// #define PORT 4356
// #include <iostream>
// #include "../includes/SocketHandler.hpp"

// int main(int av, char **ar)
// {
//     if (av < 2)
//         return 1;
//     if (std::string(ar[1]) != "server") {
//         RType::Utils::SocketHandler client(IP, PORT);
//         RType::Utils::MessageParsed_s msg;
//         msg.senderIp = IP;
//         msg.senderPort = PORT + std::rand() % 1000;
//         msg.msgType = 200;
//         msg.bytes[0] = 12;
//         msg.bytes[1] = 21;
//         msg.bytes[2] = 20;
//         msg.bytes[3] = 90;
//         msg.bytes[4] = 33;
//         msg.bytes[5] = 10;
//         msg.bytes[6] = 19;
//         msg.bytes[7] = 232;
//         client.send(msg);
//         return 0;
//     }
//     RType::Utils::SocketHandler server(IP, PORT);
//     while (1) {
//         RType::Utils::MessageParsed_s rec = server.receive();
//         std::printf("type %d\n", rec.msgType);
//         for (unsigned char i = 0; i < 8; ++i)
//             std::printf("byte %d  = |%d|\n", i, rec.bytes[i]);
//     }
//     return 0;
// }