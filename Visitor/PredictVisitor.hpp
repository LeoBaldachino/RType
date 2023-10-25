/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PredictVisitior
*/

#pragma once
#include "IVisitor.hpp"
#include "../Systems/PlayerSystem.hpp"
#include "../Systems/BydosSystem.hpp"
#include "../Systems/TourreSystem.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Systems/TourreSystem.hpp"
#include "../Systems/Subsystems/PredictShoot.hpp"

class PredictVisitor : public IVisitor {
    public:
        PredictVisitor()
        {}
        ~PredictVisitor() {};
        void visitPlayer(Player &p, Core &core) {
            (void)core;
            this->_playerSystem.updatePos(p);
            // p._inputs->lockInputs();
            // this->_playerSystem.createPiercingShots(p, core);
            // this->_playerSystem.createShots(p, core);
            // p._inputs->unlockInputs();
            while (!p._inputs->isEmpty())
                p._inputs->popEvent();
        };
        void visitBydos(Bydos &b, Core &core) {
            (void)core;
            this->_bydosSystem.updatePos(b);
        }
        void visitTourre(Tourre &t, Core &core) {
            (void)core;
            this->_tourreSystem.updatePos(t);
        }
        void visitShot(ShotEntity &s, Core &core) {
            // unsigned short id = core.getEntityId(s);
            // if (id == 0)
            //     return;
            // if (this->_predictShoot.shootSetVector(id, s))
            // this->_shot.updatePos(s);
            // this->_shot.clearShots(s, core);
        }
        void visitPiercingShot(PiercingShotEntity &pS, Core &core) {
            // this->_piercingShotSystem.updatePos(pS);
            // this->_piercingShotSystem.clearShots(pS, core);
        }
    private:
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
        TourreSystem _tourreSystem;
        ShotSystem _shot;
        PredictShoot _predictShoot;
        PiercingShotSystem _piercingShotSystem;
};
