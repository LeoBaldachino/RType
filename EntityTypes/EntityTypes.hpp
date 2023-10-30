/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** EntityTypes
*/

#pragma once

namespace RType {
    enum EntityTypes {
        none,
        player,
        playerShoot,
        percingShoot,
        bydos,
        bydosShoot,
        tourre,
        coin,
        genie,
        genieShot
    };
    EntityTypes castEntity(unsigned char c) ;
}
