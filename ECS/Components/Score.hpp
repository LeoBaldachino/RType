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
#include <string>


class ScoreComponent {
    public:
        ScoreComponent(const std::string &name) {
            this->_readOnly = true;
            this->_name = name;
            this->_actScore = 0.0;
            //! do not uncomment this code, it will have some very strange behavior on the client side
            // if (!name.empty()) {            
            //     this->_readOnly = false;
            //     std::ifstream scores("all.score");
            //     std::string line;
            //     while (std::getline(scores, line))
            //         if (line.rfind(name, 0) == 0) {
            //             line.erase(0, name.size() + 1);
            //             break;
            //         }
            //     try {
            //         std::cout << "Get act score..." << "|" << line  << "|" << std::endl;
            //         this->_actScore = std::stof(line);
            //         std::cout << "stof success !" << std::endl;
            //     } catch (const std::exception &err) {
            //         std::cout << "Error when getting the score of the " << name << " entity" << std::endl;
            //     }
            // }
            std::cout << "Score end..." << std::endl;
        };
        ~ScoreComponent() {
            std::cout << "Estoy destrudos" << std::endl;
            if (!this->_readOnly) {
                std::ifstream scores;
                std::string line;
                std::string lineToFill;
                bool find = false;
                scores.open("all.score");
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
                myfile.open("all.score", std::ios::trunc);
                if (!myfile.is_open())
                    return;
                myfile << lineToFill;
                myfile.close();
            }
        };
        inline void increaseScore(const float &toIncrease) {std::cout <<"increase" << std::endl;this->_actScore+=toIncrease;std::cout << "Actual score " << this->_actScore << std::endl;};
        inline void setScore(const float &toSet) {this->_actScore=toSet;};
        inline unsigned char getScore() const {std::cout << "Get Actual score " << this->_actScore << std::endl;return static_cast<unsigned char>(this->_actScore);};
        inline std::string getName() {return this->_name;};
    protected:
        float _actScore;
        std::string _name;
        bool _readOnly;
};
