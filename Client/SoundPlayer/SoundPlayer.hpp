/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SoundPlayer
*/

#pragma once
#include "../../EntityTypes/EntityTypes.hpp"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <chrono>

namespace RType {
    class SoundPlayer {
        public:
            SoundPlayer();
            ~SoundPlayer() {};
            void playSpawnSound(const RType::EntityTypes &entityType);
            void playDeathSound(const RType::EntityTypes &entityType);
        private:
            std::unordered_map<RType::EntityTypes, std::pair<std::shared_ptr<sf::Sound>, std::shared_ptr<sf::Sound>>> _sounds;
            std::chrono::steady_clock::time_point _loopChrono;
            sf::Sound _sound;
            std::vector<std::unique_ptr<sf::SoundBuffer>> _buffers;
    };
}
