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
    Vector2d sizeFirst = first.getSize();
    Vector2d sizeSec = sec.getSize();
    Position placeFirst = first.getPosition();
    Position placeSecond = sec.getPosition();
    if (placeFirst.getX() > placeSecond.getX() + sizeSec.x)
        return false;
    if (placeFirst.getY() > placeSecond.getY() + sizeSec.y)
        return false;
    if (placeFirst.getX() + sizeFirst.x < placeSecond.getX())
        return false;
    if (placeFirst.getY() + sizeFirst.y < placeSecond.getY())
        return false;
    return true;
}