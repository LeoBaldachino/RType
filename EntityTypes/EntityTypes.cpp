/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** EntityTypes
*/

#include "EntityTypes.hpp"


RType::EntityTypes RType::castEntity(unsigned char c) 
{
    switch (c)
    {
    case RType::player :
        return  RType::player;
    case  RType::playerShoot :
        return  RType::playerShoot;
    case  RType::bydos :
        return  RType::bydos;
    case  RType::bydosShoot :
        return  RType::bydosShoot;
    default:
        return  RType::none;
    }
}