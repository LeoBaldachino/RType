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
#include "../Systems/GenieSystem.hpp"
#include "../Systems/DragonSystem.hpp"
#include "../Systems/DragonShotSystem.hpp"
#include "../Systems/CoinSystem.hpp"
#include "../Systems/GenieShotSystem.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Systems/BydosSystem.hpp"
#include "../Systems/MermaidSystem.hpp"
#include "../Systems/MermaidShotSystem.hpp"

class SystemVisitor : public IVisitor {
    public:
        SystemVisitor() {};
        void visitPlayer(Player &p, Core &core) {
            p._inputs->lockInputs();
            this->_playerSystem.updatePos(p);
            this->_playerSystem.createShots(p, core);
            p._inputs->unlockInputs();
            for (auto it : core._entities)
                if (it.second->getEntityType() == RType::bydos || it.second->getEntityType() == RType::bydosShoot
                || it.second->getEntityType() == RType::coin || it.second->getEntityType() == RType::genie
                || it.second->getEntityType() == RType::genieShot || it.second->getEntityType() == RType::dragon)
                    this->_playerSystem.checkCollision(p, *it.second, core);
            this->_lastPlayerPos = p.getPosition();
        }
        void visitBydos(Bydos &b, Core &core) {
            if (b.getLifes() == 0)
                return (void)core.removeEntityLater(b);
            this->_bydosSystem.updatePos(b);
            this->_bydosSystem.createShots(b, this->_lastPlayerPos, core);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_bydosSystem.checkCollision(b, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_bydosSystem.checkCollision(b, *it.second, core, true);
            }
        };
        void visitTourre(Tourre &t, Core &core) {
            if (t.getLifes() == 0)
                return (void)core.removeEntityLater(t);
            this->_tourreSystem.updatePos(t);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
            }
        };
        void visitGenie(Genie &g, Core &core) {
            if (g.getLifes() == 0)
                return (void)core.removeEntityLater(g);
            this->_genieSystem.updatePos(g);
            if (g.getPosition().getX() <= 1920 - 500)
                this->_genieSystem.shot(g, core);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_genieSystem.checkCollision(g, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_genieSystem.checkCollision(g, *it.second, core, true);
            }
        };
        void visitMermaid(Mermaid &m, Core &core) {
            if (m.getLifes() == 0)
                return (void)core.removeEntityLater(m);
            this->_mermaidSystem.updatePos(m);
            if (m.getPosition().getX() <= 1920 - 500)
                this->_mermaidSystem.shot(m, core);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_mermaidSystem.checkCollision(m, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_mermaidSystem.checkCollision(m, *it.second, core, true);
            }
        };
        void visitMermaidShot(MermaidShot &mS, Core &core) {
            // if (mS.getLifes() == 0) {
            //     // Position(1700 + std::rand() % 200, std::rand() % 1000, 1080, 1920
            //     Shoot tmpShoot(Vector2d(0, -1), Vector2d(std::rand() % 500, 1100), 1, 3, 1, false);
            //     // Shoot tmpShoot(Vector2d(-1, 0), Vector2d(mS.getPosition().getX(), mS.getPosition().getY()), 1, 3, 1, false);
            //     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
            //     tmpShoot.setDirection(Vector2d(0, -1));
            //     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
            //     tmpShoot.setDirection(Vector2d(0, 1));
            //     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
            //     tmpShoot.setDirection(Vector2d(1, 0));
            //     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
            //     return (void)core.removeEntityLater(mS);
            // }
            this->_mermaidShotSystem.updatePos(mS, this->_lastPlayerPos);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_mermaidShotSystem.checkCollision(mS, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_mermaidShotSystem.checkCollision(mS, *it.second, core, true);
            }
        };
        void visitDragon(Dragon &d, Core &core) {
            if (d.getLifes() == 0)
                return (void)core.removeEntityLater(d);
            this->_dragonSystem.updatePos(d);
            if (d.getPosition().getX() <= 1920 - 667)
                this->_dragonSystem.shot(d, core);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_dragonSystem.checkCollision(d, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_dragonSystem.checkCollision(d, *it.second, core, true);
            }
        };
        void visitDragonShot(DragonShot &dS, Core &core) {
            if (dS.getLifes() == 0) {
                Shoot tmpShoot(Vector2d(-1, 0), Vector2d(dS.getPosition().getX(), dS.getPosition().getY()), 1, 3, 1, false);
                core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
                tmpShoot.setDirection(Vector2d(0, -1));
                core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
                tmpShoot.setDirection(Vector2d(0, 1));
                core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
                tmpShoot.setDirection(Vector2d(1, 0));
                core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false), core.getAvailabeIndex());
                return (void)core.removeEntityLater(dS);
            }
            this->_dragonShotSystem.updatePos(dS, this->_lastPlayerPos);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_dragonShotSystem.checkCollision(dS, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_dragonShotSystem.checkCollision(dS, *it.second, core, true);
            }
        }
        void visitGenieShot(GenieShot &gS, Core &core) {
            this->_genieShotSystem.updatePos(gS);
            for (auto it : core._entities) {
                auto entityType = it.second->getEntityType();
                if (entityType == RType::playerShoot)
                    this->_genieShotSystem.checkCollision(gS, *it.second, core, false);
                if (entityType == RType::percingShoot)
                    this->_genieShotSystem.checkCollision(gS, *it.second, core, true);
            }
        }
        void visitShot(ShotEntity &s, Core &core) {
            this->_shotSystem.updatePos(s);
            this->_shotSystem.clearShots(s, core);
        };
        void visitPiercingShot(PiercingShotEntity &pS, Core &core) {
            this->_piercingShotSystem.updatePos(pS);
            this->_piercingShotSystem.clearShots(pS, core);
        };
        void visitCoin(Coin &c, Core &core) {
            this->_coinSystem.updatePos(c);
        }
    private:
        Player _lastPlayer;
        Position _lastPlayerPos;
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
        TourreSystem _tourreSystem;
        GenieSystem _genieSystem;
        ShotSystem _shotSystem;
        PiercingShotSystem _piercingShotSystem;
        CoinSystem _coinSystem;
        GenieShotSystem _genieShotSystem;
        MermaidSystem _mermaidSystem;
        MermaidShotSystem _mermaidShotSystem;
        DragonSystem _dragonSystem;
        DragonShotSystem _dragonShotSystem;
};
