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
        void visitPlayer(Player &p, Core &core) {
            this->_playerSystem.setPlayer(p);
            this->_playerSystem.getInputs();
            this->_playerSystem.updatePos();
            this->_playerSystem.createPiercingShots(core);
            this->_playerSystem.createShots(core);
            p = this->_playerSystem.getPlayer();
        }
        void visitBydos(Bydos &b, Core &core) {
            this->_bydosSystem.setBydos(b);
            this->_bydosSystem.updatePos();
            // this->_bydosSystem.createShots(this->_playerSystem.getPlayer(), core); DEFINIR CLOCK
            b = this->_bydosSystem.getBydos();
        };
        void visitTourre(Tourre &t, Core &core) {
            this->_tourreSystem.setTourre(t);
            this->_tourreSystem.updatePos();
            // this->_tourreSystem.createShots(this->_playerSystem.getPlayer(), core);
            t = this->_tourreSystem.getTourre();
        };
        void visitShot(ShotEntity &s, Core &core) {
            this->_shotSystem.updatePos(s);
            // this->_shotSystem.clearShots(s);
        };
        void visitPiercingShot(PiercingShotEntity &pS, Core &core) {
            this->_piercingShotSystem.updatePos(pS);
            // this->_piercingShotSystem.clearShots(pS);
        };
    private:
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
        TourreSystem _tourreSystem;
        ShotSystem _shotSystem;
        PiercingShotSystem _piercingShotSystem;
};
