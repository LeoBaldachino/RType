/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IVisitor.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <memory>

class Core;
class Player;
class Bydos;
class Tourre;
class ShotEntity;
class PiercingShotEntity;

class IVisitor {
    public:
        virtual void visitPlayer(Player &p, Core &core) = 0;
        virtual void visitBydos(Bydos &b, Core &core) = 0;
        virtual void visitTourre(Tourre &t, Core &core) = 0;
        virtual void visitShot(ShotEntity &s, Core &core) = 0;
        virtual void visitPiercingShot(PiercingShotEntity &pS, Core &core) = 0;
};
