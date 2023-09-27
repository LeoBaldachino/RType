/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.cpp
*/

#include "PiercingShotEntity.hpp"

PiercingShotEntity::PiercingShotEntity(Shoot &shoot) : _drawable("Assets/piercingShot.png", 1), _shoot(shoot)
{
}