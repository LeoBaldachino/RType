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
    public:
        enum Enemies {
            BYDOS,
            TOURRE,
            COIN,
            GENIE,
            MERMAID,
            DRAGON
        };
        /**
         * @brief Construct a new Parser
         * 
         * @param configFile path to the config file
         */
        Parser(std::string configFile);
        /**
         * @brief Destroy the Parser object
         * 
         */
        ~Parser () {};
        /**
         * @brief read the config file
         * 
         * @param configFile 
         */
        void readConfig(std::string configFile);
        /**
         * @brief Get the a setting from the config file
         * 
         * @tparam T the type of the setting
         * @param settingsName name of the setting
         * @return T the setting value
         */
        template<typename T>
        T getSetting(std::string settingsName);
        /**
         * @brief Get the Setting from the config file with a scope
         * 
         * @tparam T the type of the setting
         * @param settingsName name of the setting
         * @param setting the scope
         * @param errorSupp error recognition
         * @return T the setting value
         */
        template<typename T>
        T getSetting(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp = "");
        /**
         * @brief Get the Enemy setting
         * 
         * @param settingsName name of the setting
         * @param setting the scope
         * @param errorSupp error recogniton
         * @return int number of enemies
         */
        int getEnemy(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp);
        /**
         * @brief Get the Music name
         * 
         * @return std::string the music name
         */
        std::string getMusic(void) const;
        /**
         * @brief Get the current parralax
         * 
         * @return int the current parralax
         */
        int getParallax(void) const;
        /**
         * @brief Get the list of the waves
         * 
         * @return std::vector<std::map<Enemies, int>> the enenmies current waves
         */
        std::vector<std::map<Enemies, int>> getWaves(void) const;
    private:
        libconfig::Config config;
        std::unique_ptr<Error> error;
        std::string _music = "";
        int _parallaxIndex = 0;
        std::string _next_level = "";
        std::vector<std::map<Enemies, int>> _waves;
        void initMusic(void);
        void initParallax(void);
        void initWaves(void);
};
