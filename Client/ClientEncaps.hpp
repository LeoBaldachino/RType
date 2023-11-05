/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ClientEncaps
*/

#pragma once

#ifdef _WIN32
    #include <io.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <signal.h>

namespace RType {
    class ClientEncaps {
        public:
    /**
     * @brief Construct a new Client Encaps object
     * 
     */
            ClientEncaps() {};
            /**
             * @brief Destroy the Client Encaps object
             * 
             */
            ~ClientEncaps() {};
            /**
             * @brief make a fork
             * 
             * @return int the pid of the fork
             */
            int serverFork() {
                #ifdef _WIN32
                    return _spawnl(_P_NOWAIT, "RTypeServer.exe", NULL);
                #else
                    return fork();
                #endif
            }
            /**
             * @brief make a kill
             * 
             * @param pid the pid of the process
             * @param signum the signal
             * @return int return of the kill
             */
            int serverKill(int pid, int signum) {
                #ifdef _WIN32
                    return TerminateProcess((HANDLE)pid, signum);
                #else
                    return kill(pid, signum);
                #endif
            }
    };
}
