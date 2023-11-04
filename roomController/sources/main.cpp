/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** main
*/

#include "../includes/RoomController.hpp"

int main(int ac, char **av)
{
    try {
        RType::RoomController controller(ac, av);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 84;
    }
    return 0;
}