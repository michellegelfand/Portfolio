#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

/**
 * This class complies with the requirements of the handleton class.
 * It is designed to log program errors, exceptions and debug information
 * during the program's execution.
 * 
 * Project: logger.hpp 
 * Date: 17.11.19 
 * Author: Olga Komarovsky Chashka
 */

#include <iostream>/* std */
#include <iosfwd>/* ostream */
#include <fstream>/* ofstream */
#include <mutex>

#include "handleton.hpp"

namespace ilrd
{

class Logger
{
public:
    enum Severity
    {
        DEBUGER,
        INFO,
        WARNING,
        ERROR,
        NUM_OF_SEVERITIES
    };

    ~Logger();
    void Log(Severity msg_severity, const std::string& msg, 
                const std::string& file, int line);
    
    void SetOutputSevirity(Severity putput_severity = DEBUGER);
    
private:
    
    Severity m_severity;
    std::mutex m_mutex;
    std::ofstream *m_lut[2];

    //ctor in private to work with handleton
    explicit Logger(Severity severity = DEBUGER);
    friend class Handleton<Logger>;
};

}//ilrd
#endif/*  __LOGGER_HPP__ */

