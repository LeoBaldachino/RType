/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Parser.hpp
*/

#pragma once
#include "Error.hpp"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <libconfig.h++>
#include <libconfig.h>

class Parser {
    enum Enemies {
        BYDOS,
        TOURRE
    };

    public:
        Parser(std::string configFile);
        ~Parser () {};
        void readConfig(std::string configFile);
        template<typename T>
        T getSetting(std::string settingsName);
        template<typename T>
        T getSetting(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp = "");
        int getEnemy(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp);
        std::string getMusic(void) const;
        std::string getNextLevel(void) const;
        int getParallax(void) const;
        std::vector<std::map<Enemies, int>> getWaves(void) const;
    private:
        libconfig::Config config;
        std::unique_ptr<Error> error;
        std::string _music;
        int _parallaxIndex;
        std::string _next_level;
        std::vector<std::map<Enemies, int>> _waves;
        void initMusic(void);
        void initParallax(void);
        void initNextLevel(void);
        void initWaves(void);
};
