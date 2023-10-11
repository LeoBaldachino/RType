/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** HitBox
*/

#include "HitBox.hpp"

HitBox::HitBox()
{
}

HitBox::~HitBox()
{
}

bool HitBox::entityIntersect(IEntity &first, IEntity &sec)
{
    // Vector2d sizeFirst = first.getSize();
    // Vector2d sizeSec = sec.getSize();
    // Position placeFirst = first.getPosition();
    // Position placeSecond = sec.getPosition();
    // for (int x = placeFirst.getX(); x < sizeFirst.x + placeFirst.getX(); ++x)
    //     for (int y = placeFirst.getY(); y < sizeFirst.y + placeFirst.getY(); ++y)
    //         if ((x >= placeSecond.getX() && x <= placeSecond.getX() + sizeSec.x) && (y >= placeSecond.getY() && y <= placeSecond.getY() + sizeSec.y))
    //             return true;
    return false;
}