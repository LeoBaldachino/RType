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
#include "../Entity/EntityType.hpp"
#include "../Components/IsReady.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor() {};
        void visitPlayer(Player &p, Core &core) {
            this->_playerSystem.getInputs(p);
            this->_playerSystem.updatePos(p);
            // this->_playerSystem.createPiercingShots(p, core);
            // this->_playerSystem.createShots(p, core);
            for (auto it : core._entities)
                if (it.second->getEntityType() == enemyShoot)
                    this->_playerSystem.checkCollision(p, *it.second);
        }
        void visitBydos(Bydos &b, Core &core) {
            this->_bydosSystem.updatePos(b);
            this->_bydosSystem.createShots(b, this->_lastPlayer, core);
        };
        void visitTourre(Tourre &t, Core &core) {
            this->_tourreSystem.updatePos(t);
            // this->_tourreSystem.createShots(t, this->_lastPlayer, core);
        };
        void visitShot(ShotEntity &s, Core &core) {
            this->_shotSystem.updatePos(s);
            this->_shotSystem.clearShots(s, core);
        };
        void visitPiercingShot(PiercingShotEntity &pS, Core &core) {
            this->_piercingShotSystem.updatePos(pS);
            this->_piercingShotSystem.clearShots(pS, core);
        };
    private:
        Player _lastPlayer;
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
        TourreSystem _tourreSystem;
        ShotSystem _shotSystem;
        PiercingShotSystem _piercingShotSystem;
};
