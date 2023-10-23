/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Prediction
*/

#pragma once

#include "../../Entity/Player.hpp"
#include "../../Core/Core.hpp"
#include "../../EntityTypes/EntityTypes.hpp"
#include "../../Visitor/SystemVisitor.hpp"
#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../server/includes/ComCodes.hpp"
#include "../ClientEvents.hpp"
#include "../../Visitor/PredictVisitor.hpp"

#define PREDICATE_ENTITIES_TIMER 300

namespace RType {
    class Prediction {
        public:
            Prediction(Core &core, std::vector<Events> &events) : _core(core), _inputs(events) {
                this->_clockOtherEntities = std::chrono::steady_clock::now();
            };
            ~Prediction() {

            };
            void PredicatePlayer(unsigned short id, size_t delay = 20) {
                auto find = this->_core._entities.find(id);
                if (find == this->_core._entities.end())
                    return;
                auto findUpdateTime = this->_updatesTime.find(id);
                if (findUpdateTime == this->_updatesTime.end()) {
                    this->_updatesTime.insert({id, {std::chrono::steady_clock::now(), delay}});
                    findUpdateTime = this->_updatesTime.find(id);
                }
                if (findUpdateTime->second.second != delay)
                    findUpdateTime->second.second = delay;
                auto clock = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::microseconds>(clock - findUpdateTime->second.first).count() < findUpdateTime->second.second)
                    return;
                findUpdateTime->second.first = clock;
                std::shared_ptr<Player> ptrPlayer = std::dynamic_pointer_cast<Player>(find->second);
                for (auto it : this->_inputs)
                    ptrPlayer->_inputs->addEvents((Inputs::Events)(it));
            }
            void PredicateOtherEntities() {
                auto clock = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::microseconds>(clock - this->_clockOtherEntities).count() < PREDICATE_ENTITIES_TIMER)
                    return;
                this->_clockOtherEntities = clock;
                for (auto &it : this->_core._entities)
                    it.second->accept(this->_prV, this->_core);
            }
        private:
            Core &_core;
            std::vector<Events> &_inputs;
            std::unordered_map<unsigned short, std::pair<std::chrono::steady_clock::time_point, size_t>> _updatesTime;
            std::chrono::steady_clock::time_point _clockOtherEntities;
            PredictVisitor _prV;
    };
}
