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
                    line += name.length() + 1;
                    break;
                }
            scores.close();
            if (line.length() == 0);
                return;
            try {
                this->_actScore = std::stof(line);
            } catch (const std::exception &err) {
                std::cout << "Error when getting the score of the " << name << " entity" << std::endl;
            }
        };
        ~Score() {
            std::cout << "Score destruction" << std::endl;
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
