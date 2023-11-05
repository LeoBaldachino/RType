/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Coins.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../../EntityTypes/EntityTypes.hpp"

#define MOVE_SPEED 3
#define COIN_X 103
#define COIN_Y 130

class Coin : public IEntity {
    public:
        Coin(Position position);
        ~Coin() {};
        void accept(IVisitor &v, Core &core);
        void setMoveable(const Moveable &moveable);
        Moveable getMoveable(void) const;
        void setPosition(const Position &position);
        Position getPosition(void) const;
        Vector2d getSize(void);
        bool getHasMoved(void);
        void setHasMoved(bool state);
        inline unsigned char getEntityType() { return (RType::coin); }
        unsigned int getEntitySpriteFrame();
        std::vector<float> getEntityPositionRange();
        void setTempoState(ClockTimer state);
        ClockTimer getTempoState();
        /**
         * @brief Checks if the entity is ready to move
         * @return bool
         */
        inline bool readyToMove() {return this->_readyMove.clockOk();};

    private:
        Position _position;
        Moveable _movement;
        int _velocity = 1;
        Vector2d _size;
        bool _hasMoved = false;
        unsigned int _spriteFrame = 0;
        ClockTimer _frameClock;
        ClockTimer _currentTempoState;
        ClockTimer _readyMove;
};
