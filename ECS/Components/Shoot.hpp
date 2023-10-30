/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Shoot.hpp
*/

#pragma once
#include "Vector2d.hpp"

/**
 * @class Shoot
 * @brief Class representing a Shoot object
 */
class Shoot {
    public:
        /**
         * @brief Construct a new Shoot object
         * 
         * @param direction The direction of the shoot
         * @param origin The origin of the shoot
         * @param dmg The damage of the shoot
         * @param velocity The velocity of the shoot
         * @param gravity The gravity of the shoot
         * @param whoShot The entity who shot
         */
        Shoot(Vector2d direction, Vector2d origin, int dmg, int velocity, float gravity, bool whoShot) {
            this->_direction = direction;
            this->_origin = origin;
            this->_dmg = dmg;
            this->_velocity = velocity;
            this->_gravity = gravity;
            this->_whoShot = whoShot;
        }

        /**
         * @brief Get the Direction object
         * 
         * @return Vector2d 
         */
        Vector2d getDirection(void) const { return(this->_direction); }

        /**
         * @brief Get the Origin object
         * 
         * @return Vector2d 
         */
        Vector2d getOrigin(void) const { return(this->_origin); }

        /**
         * @brief Get the Damage object
         * 
         * @return int 
         */
        int getDmg(void) const { return(this->_dmg); }

        /**
         * @brief Get the Velocity object
         * 
         * @return int 
         */
        int getVelocity(void) const { return(this->_velocity); }

        /**
         * @brief Get the Gravity object
         * 
         * @return float 
         */
        float getGravity(void) const { return(this->_gravity); }

        /**
         * @brief Get the Who Shot object
         * 
         * @return bool 
         */
        bool getWhoShot(void) const { return(this->_whoShot); }
        
        /**
         * @brief Set the Direction object
         * 
         * @param direction 
         */
        void setDirection(const Vector2d &direction) { this->_direction = direction; }

        /**
         * @brief Set the Origin object
         * 
         * @param origin 
         */
        void setOrigin(const Vector2d &origin) { this->_origin = origin; }

        /**
         * @brief Set the Damage object
         * 
         * @param dmg 
         */
        void setDmg(const int &dmg) { this->_dmg = dmg; }

        /**
         * @brief Set the Velocity object
         * 
         * @param velocity 
         */
        void setVelocity(const int &velocity) { this->_velocity = velocity; }

        /**
         * @brief Set the Gravity object
         * 
         * @param gravity 
         */
        void setGravity(const float &gravity) { this->_gravity = gravity; }

        /**
         * @brief Set the Who Shot object
         * 
         * @param whoShot 
         */
        void setWhoShot(const bool &whoShot) { this->_whoShot = whoShot; }

        /**
         * @brief Destroy the Shoot object
         */
        ~Shoot() {};

    private:
        Vector2d _direction; ///< The direction of the shoot
        Vector2d _origin; ///< The origin of the shoot
        int _dmg; ///< The damage of the shoot
        int _velocity; ///< The velocity of the shoot
        float _gravity; ///< The gravity of the shoot
        bool _whoShot; ///< True if shot by the player false otherwise
};
