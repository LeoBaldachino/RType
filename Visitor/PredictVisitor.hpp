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

class PredictVisitor : public IVisitor {
    public:
        PredictVisitor()
        {}
        ~PredictVisitor() {};
        void visitPlayer(Player &p, Core &core) {
            (void)core;
            this->_playerSystem.updatePos(p);
        };
        void visitBydos(Bydos &b, Core &core) {
            (void)core;
            this->_bydosSystem.updatePos(b);
        }
        void visitTourre(Tourre &t, Core &core) {
            (void)core;
        }
        void visitShot(ShotEntity &s, Core &core) {

        }
        void visitPiercingShot(PiercingShotEntity &pS, Core &core) {

        }
    private:
        PlayerSystem _playerSystem;
        BydosSystem _bydosSystem;
};
