/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Error.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <memory>

class Error: public std::exception
{
    public:
        explicit Error(const std::string logsName) { _logs = std::ofstream(logsName, std::ofstream::out); }
        virtual const void writeLogs(const std::string str) { _logs << str; }
        virtual ~Error() noexcept { _logs.close(); }
    protected :
        std::ofstream _logs;
};
