/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ClientEncaps
*/

#pragma once
#include<unistd.h>
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
                return fork();
            }
            /**
             * @brief make a kill
             * 
             * @param pid the pid of the process
             * @param signum the signal
             * @return int return of the kill
             */
            int serverKill(int pid, int signum) {
                return kill(pid, signum);
            }
    };
}
