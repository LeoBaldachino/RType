/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Texture.hpp
*/

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Texture {
    public:
        Texture() {
            this->bydosTexture.loadFromFile("./../Assets/EntitiesSprites/Bydos.png");
            this->tourreTexture.loadFromFile("./../Assets/tourre.png");
            this->playerTexture.loadFromFile("./../Assets/EntitiesSprites/CupHead.png");
            this->otherPlayerTexture.loadFromFile("./../Assets/EntitiesSprites/MugMan.png");
            this->playerShotTexture.loadFromFile("./../Assets/shot.png");
            this->piercingShotTexture.loadFromFile("./../Assets/EntitiesSprites/PiercingShot.png");
            this->enemyShotTexture.loadFromFile("./../Assets/EntitiesSprites/EnemyShot.png");
        }

        sf::Texture tourreTexture;
        sf::Texture bydosTexture;
        sf::Texture playerTexture;
        sf::Texture otherPlayerTexture;
        sf::Texture playerShotTexture;
        sf::Texture piercingShotTexture;
        sf::Texture enemyShotTexture;
};
