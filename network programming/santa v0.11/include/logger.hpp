
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iosfwd>
#include <iostream>//cerr
#include <fstream>//ofstream to log in files
#include <sstream>//ostringstream
#include <mutex>//std::mutex
#include <thread>//thread id

#include "lock_guard.hpp"
#include "handleton.hpp"


namespace ilrd
{

class Logger
{
public:
    enum Severity { DEBUG, INFO, WARNING, ERROR };

    explicit Logger(Severity initialSeverity = DEBUG,
                     std::ostream& initialOutput = std::cerr);

 /*    void init_logger(Severity initialSeverity = WARNING, std::ostream& initialOutput = std::cerr); */

    void Log(Severity severity,
                        std::thread::id thread_id, 
                        const std::string& error_type,
                        const std::string& file,
                        int line, 
                        const char *msg);

    void Log(Severity severity,
                        std::thread::id thread_id, 
                        const std::string& error_type,
                        const std::string& file,
                        int line, 
                        const std::string &msg);

    void SetOutputSeverity(Severity SetOutputSeverity);
    void SetOutput(std::ostream &output);

private:
    Severity m_severity;
    std::ostream *m_outputs[2];
    std::mutex m_mutex;

    friend class Handleton<Logger>; 
};

}//ilrd

#endif  
