/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SoundPlayer
*/

#include "SoundPlayer.hpp"

RType::SoundPlayer::SoundPlayer()
{
    std::vector<std::string> sounds = {"../Assets/fire.ogg", "../Assets/fireK.ogg"};
    int cp = 0;
    for (auto it : sounds) {
        this->_buffers.push_back(std::make_unique<sf::SoundBuffer>());
        this->_buffers.back()->loadFromFile(it);
    }
    this->_sounds.insert({RType::playerShoot, {std::make_shared<sf::Sound>(), std::make_shared<sf::Sound>()}});
    this->_sounds[RType::playerShoot].first->setBuffer(*this->_buffers[0]);
    this->_sounds[RType::playerShoot].second->setBuffer(*this->_buffers[1]);
    this->_loopChrono = std::chrono::steady_clock::now();
}

void RType::SoundPlayer::playSpawnSound(const RType::EntityTypes &entityType)
{
    auto it = this->_sounds.find(entityType);
    if (it == this->_sounds.end())
        return;
    // auto clock = std::chrono::steady_clock::now();
    // if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_loopChrono).count() < 1000)
    //     return;
    // this->_loopChrono = clock;
    if (it->second.first->getStatus() != sf::SoundSource::Status::Playing)
        it->second.first->play();
}

void RType::SoundPlayer::playDeathSound(const RType::EntityTypes &entityType)
{
    auto it = this->_sounds.find(entityType);
    if (it == this->_sounds.end())
        return;
    if (it->second.first->getStatus() != sf::SoundSource::Status::Playing)
        it->second.second->play();
}
