/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** main
*/

#include "Client.hpp"

int main(int ac, char **av)
{
    try {
        RType::Client(ac, av);
    } catch (const std::exception &err) {
        std::cout << "Error " << err.what() << std::endl;
        return 1;
    }
    return 0;
}