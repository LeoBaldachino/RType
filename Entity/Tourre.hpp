/**
 * @file Tourre.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Tourre class definition
 */

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Entity/Player.hpp"

/**
 * @brief Class representing Tourre in the game
 */
class Tourre : public IEntity {
    public:
        /**
         * @brief Construct a new Tourre object
         */
        Tourre() {};

        /**
         * @brief Construct a new Tourre object
         * 
         * @param position Position of the Tourre
         * @param velocity Velocity of the Tourre
         * @param moveDirection Direction of the Tourre movement
         */
        Tourre(Position position, int velocity, Vector2d moveDirection);

        /**
         * @brief Destroy the Tourre object
         */
        ~Tourre(){};

        void accept(IVisitor &v, Core &core);

        Shoot shoot(const Position &playerPos) const;

        void setPosition(const Position &position);
        Position getPosition() const;

        void setState(State state);
        State getState() const;

        void setVelocity(int velocity);
        int getVelocity(void) const;

        void setShootDmg(int shootDmg);
        int getShootDmg(void) const;

        void setShootVelocity(int shootVelocity);
        int getShootVelocity(void) const;

        void setShootGravity(int shootGravity);
        int getShootGravity(void) const;

        void setMoveable(const Moveable &moveable);
        Moveable getMoveable(void) const;

        
        Vector2d getSize(void) { return (Vector2d(0, 0)); };
        inline unsigned char getEntityType() {return RType::tourre;}
        bool getHasMoved(void);
        void setHasMoved(bool state);

    private:
        State _state;
        Position _position;
        Moveable _movement;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        bool _hasMoved = false;
};