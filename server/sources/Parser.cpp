/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Parser.cpp
*/

#include "../includes/Parser.hpp"

Parser::Parser(std::string configFile)
{
    this->error = std::make_unique<Error>("logs.txt");
    this->readConfig(configFile);
}

void Parser::readConfig(std::string configFile)
{
    try {
        config.readFile(configFile.c_str());
    } catch (libconfig::FileIOException &e) {
        std::cerr << "Could not read file : " << configFile << std::endl;
        exit(84);
    } catch (libconfig::ParseException &e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
        exit(84);
    }
    this->initMusic();
    this->initParallax();
    this->initNextLevel();
    this->initWaves();
}

void Parser::initMusic(void)
{
    try {
        this->_music = this->getSetting<std::string>("music.filepath");
    }
    catch (std::logic_error &e) {
        return;
    }
}

void Parser::initParallax(void)
{
    this->_parallaxIndex = this->getSetting<int>("parallax.index");
}

void Parser::initNextLevel(void)
{
    try {
        this->_next_level = this->getSetting<std::string>("next-level.filepath");
    }
    catch (std::logic_error &e) {
        return;
    }
}

void Parser::initWaves(void)
{
    std::string e = " for wave ";
    try {
        const libconfig::Setting &waves = this->config.getRoot()["enemies"]["waves"];
        int wavesLen = waves.getLength();
        for (int i = 0; i < wavesLen; ++i) {
            const libconfig::Setting &wave = waves[i];
            int bydosCount = this->getEnemy("bydos", wave, e + std::to_string(i + 1));
            int tourreCount = this->getEnemy("tourre", wave, e + std::to_string(i + 1));
            std::map<Enemies, int> tmpMap = {{Enemies::BYDOS, bydosCount}, {Enemies::TOURRE, tourreCount}};
            this->_waves.push_back(tmpMap);
        }
    } catch (const libconfig::SettingNotFoundException &e) {
        this->error->writeLogs("No waves setting in configuration file\n");
    }
}

template<typename T>
T Parser::getSetting(std::string settingsName)
{
    try {
        return T(config.lookup(settingsName));
    } catch (libconfig::SettingNotFoundException &e) {
        this->error->writeLogs("No " + settingsName + " setting in configuration file.\n");
        return (T(NULL));
    } catch (libconfig::SettingTypeException &e) {
        if (typeid(T).hash_code() == typeid(int).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be an int.\n");
        if (typeid(T).hash_code() == typeid(std::string).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a string.\n");
        if (typeid(T).hash_code() == typeid(float).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a float.\n");
        if (typeid(T).hash_code() == typeid(double).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a double.\n");
        return (T(NULL));
    }
    return (T(NULL));
}


int Parser::getEnemy(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp)
{
    try {
        return (setting.lookup(settingsName));
    } catch (libconfig::SettingNotFoundException &e) {
        return (0);
    } catch (libconfig::SettingTypeException &e) {
        return (0);
    }
    return (0);
}

template<typename T>
T Parser::getSetting(std::string settingsName, const libconfig::Setting &setting, const std::string errorSupp)
{
    try {
        return T(setting.lookup(settingsName));
    } catch (libconfig::SettingNotFoundException &e) {
        this->error->writeLogs("No " + settingsName + " setting in configuration file" + errorSupp + ".\n");
        return (T(NULL));
    } catch (libconfig::SettingTypeException &e) {
        if (typeid(T).hash_code() == typeid(int).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be an int" + errorSupp + ".\n");
        if (typeid(T).hash_code() == typeid(std::string).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a string" + errorSupp + ".\n");
        if (typeid(T).hash_code() == typeid(float).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a float" + errorSupp + ".\n");
        if (typeid(T).hash_code() == typeid(double).hash_code())
            this->error->writeLogs("Type of " + settingsName + " must be a double" + errorSupp + ".\n");
        return (T(NULL));
    }
    return (T(NULL));
}
