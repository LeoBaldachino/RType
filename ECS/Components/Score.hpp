/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ScoreController
*/

#pragma once
#include <iostream>
#include <fstream>
#include <mutex>

#define FILENAME "all.score"

class Score {
    public:
        Score(const std::string &name) {
            if (name.empty()) {
                this->_readOnly = true;
                return;
            }
            this->_readOnly = false;
            this->_name = name;
            this->_actScore = 0.0;
            std::ifstream scores;
            std::string line;
            scores.open(FILENAME);
            if (!scores.is_open())
                return;
            while (std::getline(scores, line))
                if (line.rfind(name, 0) == 0) {
                    std::cout << "Find line !" << std::endl;
                    line.erase(0, name.size() + 1);
                    break;
                }
            scores.close();
            try {
                std::cout << "Get act score..." << std::endl;
                this->_actScore = std::stof(line);
            } catch (const std::exception &err) {
                std::cout << "Error when getting the score of the " << name << " entity" << std::endl;
            }
        };
        ~Score() {
            if (this->_readOnly)
                return;
            std::ifstream scores;
            std::string line;
            std::string lineToFill;
            bool find = false;
            scores.open(FILENAME);
            if (scores.is_open()) {
                while (std::getline(scores, line)) {
                    if (line.rfind(this->_name, 0) == 0) {
                        find = true;
                        line = this->_name + " " + std::to_string(this->_actScore);
                    }
                    lineToFill += line + "\n";
                }
                scores.close();
            }
            if (!find) {
                lineToFill += this->_name + " " + std::to_string(this->_actScore);
            }
            std::ofstream myfile;
            myfile.open(FILENAME, std::ios::trunc);
            if (!myfile.is_open())
                return;
            myfile << lineToFill;
            myfile.close();
        };
        inline void increaseScore(const float &toIncrease) {this->_actScore+=toIncrease;std::cout << "Actual score " << this->_actScore << std::endl;};
        inline void setScore(const float &toSet) {this->_actScore=toSet;};
        inline unsigned char getScore() const {return static_cast<unsigned char>(this->_actScore);};
        inline std::string getName() {return this->_name;};
    protected:
        float _actScore;
        std::string _name;
        bool _readOnly;
};
