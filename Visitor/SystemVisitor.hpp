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
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor() {};
        void visitPlayer(Player &p, Core &core) {
            this->_playerSystem.updatePos(p);
            this->_playerSystem.createPiercingShots(p, core);
            this->_playerSystem.createShots(p, core);
            for (auto it : core._entities)
                if (it.second->getEntityType() == RType::bydos || it.second->getEntityType() == RType::bydosShoot)
                    this->_playerSystem.checkCollision(p, *it.second, core);
        }
        void visitBydos(Bydos &b, Core &core) {
            if (b.getLifes() == 0)
                return (void)core.removeEntityLater(b);
            this->_bydosSystem.updatePos(b);
            this->_bydosSystem.createShots(b, this->_lastPlayer, core);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_bydosSystem.checkCollision(b, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_bydosSystem.checkCollision(b, *it.second, core, true);
            }
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
