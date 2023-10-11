/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/Drawable.hpp"
#include "IEntity.hpp"
#include "EntityType.hpp"

#define PIERCING_SHOT_X 80
#define PIERCING_SHOT_Y 16

class PiercingShotEntity : public IEntity {
    public:
        PiercingShotEntity(Shoot &shoot);
        ~PiercingShotEntity() {};

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
        inline unsigned char getEntityType() {return percingShoot;}

        bool getHasMoved(void);
        void setHasMoved(bool state);

    private:
        Shoot _shoot;
        Drawable _drawable;
        Vector2d _size;
        bool _hasMoved = false;
};
