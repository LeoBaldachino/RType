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
#include "../Systems/TourreSystem.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor(){};
        void visitPlayer(Player &p) {
            this->_playerSystem.setPlayer(p);
            // this->_playerSystem.draw(window);
            // this->_playerSystem.drawShots(window);
            // this->_playerSystem.drawPiercingShots(window);
            this->_playerSystem.getInputs();
            this->_playerSystem.updatePos();
            this->_playerSystem.updateShots();
            this->_playerSystem.updatePiercingShots();
            this->_playerSystem.createShots();
            this->_playerSystem.createPiercingShots();
            this->_playerSystem.clearShots();
            p = this->_playerSystem.getPlayer();
        }
        void visitBydos(Bydos &b) {
            this->_bydosSystem.setBydos(b);
            // this->_bydosSystem.draw(window);
            // this->_bydosSystem.drawShots(window);
            this->_bydosSystem.updatePos();
            this->_bydosSystem.updateShots();
            // this->_bydosSystem.createShots(this->_playerSystem.getPlayer()); DEFINIR CLOCK
            this->_bydosSystem.clearShots();
            b = this->_bydosSystem.getBydos();
        };
        void visitTourre(Tourre &t) {
            this->_tourreSystem.setTourre(t);
            this->_tourreSystem.updatePos();
            this->_tourreSystem.updateShots();
            // this->_tourreSystem.createShots(this->_playerSystem.getPlayer());
            this->_tourreSystem.clearShots();
            t = this->_tourreSystem.getTourre();
        };
    private:
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
        TourreSystem _tourreSystem;
};
