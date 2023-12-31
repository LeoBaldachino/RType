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

class Texture
{
public:
    Texture()
    {
        this->bydosTexture.loadFromFile("./Assets/EntitiesSprites/Bydos.png");
        this->tourreTexture.loadFromFile("./Assets/EntitiesSprites/Cupcake.png");
        this->playerTexture.loadFromFile("./Assets/EntitiesSprites/CupHead.png");
        this->otherPlayerTexture.loadFromFile("./Assets/EntitiesSprites/MugMan.png");
        this->coinTexture.loadFromFile("./Assets/EntitiesSprites/Coin.png");
        this->playerShotTexture.loadFromFile("./Assets/shot.png");
        this->piercingShotTexture.loadFromFile("./Assets/EntitiesSprites/PiercingShot.png");
        this->enemyShotTexture.loadFromFile("./Assets/EntitiesSprites/EnemyShot.png");
        this->genieTexture.loadFromFile("./Assets/Genie/Genie.png");
        this->genieShotTexture.loadFromFile("./Assets/Genie/genieShot.png");
        this->mermaidTexture.loadFromFile("./Assets/Mermaid/Mermaid.png");
        this->genieTexture.loadFromFile("./Assets/Genie/Genie.png");
        this->dragonTexture.loadFromFile("./Assets/Dragon/Dragon/dragon.png");
        this->dragonShotTexture.loadFromFile("./Assets/Dragon/DragonShot/dragonShot.png");
        this->genieShotTexture.loadFromFile("./Assets/Genie/genieShot.png");
        this->mermaidShotTexture.loadFromFile("./Assets/Mermaid/MermaidShots.png");
        for (int i = 0; i != 24; ++i) {
            sf::Texture _text;
            std::string fileName = "./Assets/Desert/Desert/desert";
            fileName += std::to_string(i) + ".png";
            _text.loadFromFile(fileName);
            this->desert.push_back(_text);
        }
        this->desertForest.loadFromFile("./Assets/Desert/Background/ForestDesert.png");
        this->desertMountain.loadFromFile("./Assets/Desert/Background/MoutainsDesert.png");
        this->desertSky.loadFromFile("./Assets/Desert/Background/SkyDesert.png");
        for (int i = 0; i != 8; ++i) {
            sf::Texture _text;
            std::string fileName = "./Assets/ScreenFX/screenFX";
            fileName += std::to_string(i) + ".png";
            _text.loadFromFile(fileName);
            this->screenFX.push_back(_text);
        }

        this->gnomeSky.loadFromFile("./Assets/Gnome/Background/GnomeSky.png");
        this->gnomeMountainsFirst.loadFromFile("./Assets/Gnome/Background/GnomeMountainsFirst.png");
        this->gnomeMountainsSecond.loadFromFile("./Assets/Gnome/Background/GnomeMountainsSecond.png");
        this->gnomeFarMountains.loadFromFile("./Assets/Gnome/Background/GnomeFarMountains.png");
        this->gnomeMidMountains.loadFromFile("./Assets/Gnome/Background/GnomeMidMountains.png");
        this->gnomeLargeClouds.loadFromFile("./Assets/Gnome/Background/GnomeBigClouds.png");
        this->gnomeMediumClouds.loadFromFile("./Assets/Gnome/Background/GnomeMediumClouds.png");
        this->gnomeSmallClouds.loadFromFile("./Assets/Gnome/Background/GnomeSmallClouds.png");

        this->dragonSky.loadFromFile("./Assets/Dragon/Background/dragonSky.png");
        this->dragonBackCloudsFirst.loadFromFile("./Assets/Dragon/Background/dragonBackCloudsFirst.png");
        this->dragonBackCloudsSecond.loadFromFile("./Assets/Dragon/Background/dragonBackCloudsTwo.png");
        this->dragonBackCloudsThird.loadFromFile("./Assets/Dragon/Background/dragonBackCloudsThree.png");
        this->dragonForeCloudsFirst.loadFromFile("./Assets/Dragon/Foreground/dragonForeCloudsFirst.png");
        this->dragonForeCloudsSecond.loadFromFile("./Assets/Dragon/Foreground/dragonForeCloudsTwo.png");
        this->dragonForeCloudsThird.loadFromFile("./Assets/Dragon/Foreground/dragonForeCloudsThree.png");
        for (int i = 1; i != 7; ++i) {
            sf::Texture _text;
            std::string fileName = "./Assets/Dragon/Tower/tower";
            fileName += std::to_string(i) + ".png";
            _text.loadFromFile(fileName);
            this->tower.push_back(_text);
        }
    }

    sf::Texture tourreTexture;
    sf::Texture bydosTexture;
    sf::Texture playerTexture;
    sf::Texture otherPlayerTexture;
    sf::Texture playerShotTexture;
    sf::Texture piercingShotTexture;
    sf::Texture enemyShotTexture;
    sf::Texture genieTexture;
    sf::Texture dragonTexture;
    sf::Texture dragonShotTexture;
    sf::Texture genieShotTexture;
    sf::Texture coinTexture;
    sf::Texture mermaidTexture;
    sf::Texture mermaidShotTexture;

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

    sf::Texture dragonSky;
    sf::Texture dragonBackCloudsFirst;
    sf::Texture dragonBackCloudsSecond;
    sf::Texture dragonBackCloudsThird;
    sf::Texture dragonForeCloudsFirst;
    sf::Texture dragonForeCloudsSecond;
    sf::Texture dragonForeCloudsThird;
    std::vector<sf::Texture> tower;
};
