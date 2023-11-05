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
    this->initWaves();
}

void Parser::initMusic(void)
{
    try {
        this->_music = this->getSetting<int>("music.index");
        this->_music = this->_music > 9 || this->_music < 1 ? 1 : this->_music;
    }
    catch (std::logic_error &e) {
        return;
    }
}

void Parser::initParallax(void)
{
    this->_parallaxIndex = this->getSetting<int>("parallax.index");
    this->_parallaxIndex = this->_parallaxIndex > 3 || this->_parallaxIndex < 1 ? 1 : this->_parallaxIndex;
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
            int coinCount = this->getEnemy("coin", wave, e + std::to_string(i + 1));
            int genieCount = this->getEnemy("genie", wave, e + std::to_string(i + 1));
            int mermaidCount = this->getEnemy("mermaid", wave, e + std::to_string(i + 1));
            int bossCount = 0;
            if (genieCount > 1) {
                this->error->writeLogs("Only one genie can be spawned\n");
                genieCount = 1;
            }
            if (mermaidCount > 1) {
                this->error->writeLogs("Only one mermaid can be spawned\n");
                mermaidCount = 1;
            }
            int dragonCount = this->getEnemy("dragon", wave, e + std::to_string(i + 1));
            if (dragonCount > 1) {
                this->error->writeLogs("Only one dragon can be spawned\n");
                dragonCount = 1;
            }
            bossCount += dragonCount == 1 ? 1 : 0;
            bossCount += genieCount == 1 ? 1 : 0;
            bossCount += mermaidCount == 1 ? 1 : 0;
            if (bossCount >= 2) {
                if (dragonCount == 1) {
                    genieCount = 0;
                    mermaidCount = 0;
                }
                if (genieCount == 1)
                    mermaidCount = 0;
                this->error->writeLogs("Only one boss can be spawned at once\n");
            }
            std::map<Enemies, int> tmpMap = {{Enemies::BYDOS, bydosCount}, {Enemies::TOURRE, tourreCount}, {Enemies::COIN, coinCount}, {Enemies::GENIE, genieCount}, {Enemies::DRAGON, dragonCount}, {Enemies::MERMAID, mermaidCount}};
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
        T tmp = config.lookup(settingsName);
        return (tmp);
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

int Parser::getMusic(void) const
{
    return (this->_music);
}

int Parser::getParallax(void) const
{
    return (this->_parallaxIndex);
}

std::vector<std::map<Parser::Enemies, int>> Parser::getWaves(void) const
{
    return (this->_waves);
}
