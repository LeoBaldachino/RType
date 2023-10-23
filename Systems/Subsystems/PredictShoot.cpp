/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PredictShoot
*/

#include "PredictShoot.hpp"

PredictShoot::PredictShoot()
{
}

PredictShoot::~PredictShoot()
{
}


bool PredictShoot::shootSetVector(unsigned short id, ShotEntity &s)
{
    auto find = this->_shootPositions.find(id);
    Position actPos = s.getPosition();
    if (actPos.getX() == -20 && actPos.getY() == -20)
        return false;
    if (find != this->_shootPositions.end() && (find->second.second.x != 0 && find->second.second.y != 0 && s.getShoot().getDirection().x != 0 && s.getShoot().getDirection().y != 0))
        return true;
    if (find == this->_shootPositions.end()) {
        this->_shootPositions.insert({id, {Vector2d(0, 0), Vector2d(0, 0)}});
        find = this->_shootPositions.find(id);
    }
    if (find->second.first.x == 0 && find->second.first.y == 0) {
        find->second.first = Vector2d(actPos.getX(), actPos.getY());
        find->second.second = Vector2d(0, 0);
        return false;
    }
    if ((find->second.second.x == 0 && find->second.second.y == 0) && (find->second.first.x != actPos.getX() || find->second.first.y != actPos.getY())) {
        find->second.second = Vector2d(actPos.getX(), actPos.getY());
        Vector2d dirVec(find->second.second.x - find->second.first.x, find->second.second.y - find->second.first.y);
        Shoot oldShoot = s.getShoot();
        this->checkShootTooFast(dirVec);
        oldShoot.setDirection(dirVec);
        std::cout << "Shoot direction x = " << dirVec.x << " y = " << dirVec.y << std::endl; 
        s.setShoot(oldShoot);
        return true;
    }
    return false;
}

void PredictShoot::checkShootTooFast(Vector2d &shoot)
{
    bool areNull[2] = {false, false};
    if (shoot.x < 0.0) {
        areNull[0] = true,
        shoot.x *= -1.0;
    }
    if (shoot.y < 0.0) {
        areNull[1] = true,
        shoot.y *= -1.0;
    }
    while (shoot.x / 10.0 > 0.05 && shoot.y / 10.0 > 0.05) {
        shoot.x /= 10.0;
        shoot.y /= 10.0;
    }
    if (areNull[0])
        shoot.x *= -1;
    if (areNull[1])
        shoot.y *= -1;
}