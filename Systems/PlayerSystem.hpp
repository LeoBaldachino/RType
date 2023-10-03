/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.hpp
*/

#pragma once
#include <memory>
#include "../Entity/Player.hpp"
#include "Subsystems/InputSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/PiercingShotSystem.hpp"

class PlayerSystem {
    public:
        PlayerSystem() {};
        ~PlayerSystem() {};
        void setPlayer(const Player &p);
        Player getPlayer(void) const;
        void getInputs(void);
        void updatePos(void);
        void updateShots(void);
        // void draw(std::unique_ptr<sf::RenderWindow> &window);
        // void drawShots(std::unique_ptr<sf::RenderWindow> &window);
        // void drawPiercingShots(std::unique_ptr<sf::RenderWindow> &window);
        void createShots(void);
        void updatePiercingShots(void);
        void createPiercingShots(void);
        void clearShots(void);
    private:
        Player _player;
        InputSystem _inputSystem;
        std::unique_ptr<DrawSystem> _drawSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;
        std::vector<std::unique_ptr<PiercingShotSystem>> _piercingShots;
};