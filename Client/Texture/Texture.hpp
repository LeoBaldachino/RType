/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Texture.hpp
*/

#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Texture {
    public:
        Texture() {
            this->bydosTexture.loadFromFile("./../Assets/EntitiesSprites/Bydos.png");
            this->tourreTexture.loadFromFile("./../Assets/EntitiesSprites/Cupcake.png");
            this->playerTexture.loadFromFile("./../Assets/EntitiesSprites/CupHead.png");
            this->otherPlayerTexture.loadFromFile("./../Assets/EntitiesSprites/MugMan.png");
            this->playerShotTexture.loadFromFile("./../Assets/shot.png");
            this->piercingShotTexture.loadFromFile("./../Assets/EntitiesSprites/PiercingShot.png");
            this->enemyShotTexture.loadFromFile("./../Assets/EntitiesSprites/EnemyShot.png");
            for (int i = 0; i != 24; ++i) {
                sf::Texture _text;
                std::string fileName = "./../Assets/Desert/Desert/desert";
                fileName += std::to_string(i) + ".png";
                _text.loadFromFile(fileName);
                this->desert.push_back(_text);
            }
            this->desertForest.loadFromFile("./../Assets/Desert/Background/genie_bg_forest_sunny.png");
            this->desertMountain.loadFromFile("./../Assets/Desert/Background/genie_bg_mountains_sunny.png");
            this->desertSky.loadFromFile("./../Assets/Desert/Background/genie_bg_sky_loop.png");

            for (int i = 0; i != 8; ++i) {
                sf::Texture _text;
                std::string fileName = "./../Assets/ScreenFX/screenFX";
                fileName += std::to_string(i) + ".png";
                _text.loadFromFile(fileName);
                this->screenFX.push_back(_text);
            }
        }

        sf::Texture tourreTexture;
        sf::Texture bydosTexture;
        sf::Texture playerTexture;
        sf::Texture otherPlayerTexture;
        sf::Texture playerShotTexture;
        sf::Texture piercingShotTexture;
        sf::Texture enemyShotTexture;
        
        sf::Texture desertMountain;
        sf::Texture desertForest;
        sf::Texture desertSky;
        std::vector<sf::Texture> desert;

        std::vector<sf::Texture> screenFX;
};
