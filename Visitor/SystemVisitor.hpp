/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SystemVisitor.hpp
*/

#pragma once
#include "IVisitor.hpp"
#include "../Systems/PlayerSystem.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor(Player &p) : _playerSystem(p) {};
        void visitPlayer(Player &p, std::unique_ptr<sf::RenderWindow> &window) {
            this->_playerSystem.draw(window);
            this->_playerSystem.drawShots(window);
            this->_playerSystem.getInputs(window);
            this->_playerSystem.updatePos();
            this->_playerSystem.updateShots();
            this->_playerSystem.createShots();
        }
    private:
        PlayerSystem _playerSystem;
};
