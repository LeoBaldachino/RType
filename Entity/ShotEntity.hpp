/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/Drawable.hpp"
#include "IEntity.hpp"
#include "EntityType.hpp"
#include "../Components/ClockTimer.hpp"

#define SHOT_X 32
#define SHOT_Y 12
#define MOVE_SHOT 1

class ShotEntity : public IEntity {
    public:
        ShotEntity(Shoot &shoot, std::string spriteFile);
        ~ShotEntity() {};

        void accept(IVisitor &v, Core &core);
        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);

        Shoot getShoot(void) const;
        void setShoot(const Shoot &shoot);

        Drawable getDrawable(void) const;
        void setDrawable(const Drawable &drawable);

        Vector2d getSize(void);
        bool isColidingWith(IEntity &entity);

        Moveable getMoveable(void) const;
        void setMoveable(const Moveable &moveable);

        Position getPosition(void) const;
        void setPosition(const Position &position);

        bool getHasMoved(void);
        void setHasMoved(bool state);

        inline unsigned char getEntityType() {return enemyShoot;}
        inline bool readyToMove() {return this->_clockMove.clockOk();};
    private:
        Shoot _shoot;
        Drawable _drawable;
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _clockMove;
};
