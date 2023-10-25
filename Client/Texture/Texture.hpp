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
            this->enemyShotTexture.loadFromFile("./../Assets/EntitiesSprites/Genie.png");
            for (int i = 0; i != 24; ++i) {
                sf::Texture _text;
                std::string fileName = "./../Assets/Desert/Desert/desert";
                fileName += std::to_string(i) + ".png";
                _text.loadFromFile(fileName);
                this->desert.push_back(_text);
            }
            this->desertForest.loadFromFile("./../Assets/Desert/Background/ForestDesert.png");
            this->desertMountain.loadFromFile("./../Assets/Desert/Background/MoutainsDesert.png");
            this->desertSky.loadFromFile("./../Assets/Desert/Background/SkyDesert.png");
            for (int i = 0; i != 8; ++i) {
                sf::Texture _text;
                std::string fileName = "./../Assets/ScreenFX/screenFX";
                fileName += std::to_string(i) + ".png";
                _text.loadFromFile(fileName);
                this->screenFX.push_back(_text);
            }


            this->gnomeSky.loadFromFile("./../Assets/Gnome/Background/GnomeSky.png");
            this->gnomeMountainsFirst.loadFromFile("./../Assets/Gnome/Background/GnomeMountainsFirst.png");
            this->gnomeMountainsSecond.loadFromFile("./../Assets/Gnome/Background/GnomeMountainsSecond.png");
            this->gnomeFarMountains.loadFromFile("./../Assets/Gnome/Background/GnomeFarMountains.png");
            this->gnomeMidMountains.loadFromFile("./../Assets/Gnome/Background/GnomeMidMountains.png");
            this->gnomeLargeClouds.loadFromFile("./../Assets/Gnome/Background/GnomeBigClouds.png");
            this->gnomeMediumClouds.loadFromFile("./../Assets/Gnome/Background/GnomeMediumClouds.png");
            this->gnomeSmallClouds.loadFromFile("./../Assets/Gnome/Background/GnomeSmallClouds.png");
            // this->gnomeAloneCloudOne.loadFromFile("./../Assets/Gnome/Foreground/GnomeAloneCloudOne.png");
            // this->gnomeAloneCloudTwo.loadFromFile("./../Assets/Gnome/Foreground/GnomeAloneCloudTwo.png"); 
            // this->gnomeAloneCloudThree.loadFromFile("./../Assets/Gnome/Foreground/GnomeAloneCloudThree.png");

        }

        sf::Texture tourreTexture;
        sf::Texture bydosTexture;
        sf::Texture playerTexture;
        sf::Texture otherPlayerTexture;
        sf::Texture playerShotTexture;
        sf::Texture piercingShotTexture;
        sf::Texture enemyShotTexture;
        sf::Texture genieTexture;
        
        sf::Texture desertMountain;
        sf::Texture desertForest;
        sf::Texture desertSky;
        std::vector<sf::Texture> desert;
        std::vector<sf::Texture> screenFX;

        sf::Texture gnomeSky;
        sf::Texture gnomeMountainsFirst;
        sf::Texture gnomeMountainsSecond;
        sf::Texture gnomeFarMountains;
        sf::Texture gnomeMidMountains;
        sf::Texture gnomeLargeClouds;
        sf::Texture gnomeMediumClouds;
        sf::Texture gnomeSmallClouds;
        sf::Texture gnomeAloneCloudOne;
        sf::Texture gnomeAloneCloudTwo;
        sf::Texture gnomeAloneCloudThree;


};
