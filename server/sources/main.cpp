/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** main
*/

#include "../includes/CoreServer.hpp"

int main(int ar, char **av)
{
    try {
        RType::CoreServer server(ar, av);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}