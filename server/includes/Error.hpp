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
        /**
         * @brief Construct a new Error 
         * 
         * @param logsName name of the logfile
         */
        explicit Error(const std::string logsName) { _logs = std::ofstream(logsName, std::ofstream::out); }
        /**
         * @brief write logs to the logs file
         * 
         * @param str thing to write to the logs file
         */
        virtual const void writeLogs(const std::string str) { _logs << str; }
        /**
         * @brief Destroy the Error and close the logs file
         * 
         */
        virtual ~Error() noexcept { _logs.close(); }
    protected :
        std::ofstream _logs;
};
