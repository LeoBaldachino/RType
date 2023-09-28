/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SystemVisitor.hpp
*/

#pragma once
#include "IVisitor.hpp"
#include "../Systems/PlayerSystem.hpp"
#include "../Systems/BydosSystem.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor(){};
        void visitPlayer(Player &p, std::unique_ptr<sf::RenderWindow> &window) {
            this->_playerSystem.setPlayer(p);
            this->_playerSystem.draw(window);
            this->_playerSystem.drawShots(window);
            this->_playerSystem.drawPiercingShots(window);
            this->_playerSystem.getInputs(window);
            this->_playerSystem.updatePos();
            this->_playerSystem.updateShots();
            this->_playerSystem.updatePiercingShots();
            this->_playerSystem.createShots();
            this->_playerSystem.createPiercingShots();
            this->_playerSystem.clearShots();
            p = this->_playerSystem.getPlayer();
        }
        void visitBydos(Bydos &b, std::unique_ptr<sf::RenderWindow> &window) {
            this->_bydosSystem.setBydos(b);
            this->_bydosSystem.draw(window);
            this->_bydosSystem.drawShots(window);
            this->_bydosSystem.updatePos();
            this->_bydosSystem.updateShots();
            // this->_bydosSystem.createShots(this->_playerSystem.getPlayer());
            b = this->_bydosSystem.getBydos();
        };
    private:
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;

};
