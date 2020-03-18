
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iosfwd>
#include <iostream>//cerr
#include <fstream>//ofstream to log in files
#include <sstream>//ostringstream

class Logger
{
public:
    enum Severity { DEBUG, INFO, WARNING, ERROR };

    explicit Logger(Severity initialSeverity = WARNING,
                     std::ostream& initialOutput = std::cerr);

    void Log(Severity msgSeverity, const char *msg);
    void Log(Severity msgSeverity, const std::string &msg);

    void SetOutputSeverity(Severity SetOutputSeverity);
    void SetOutput(std::ostream &output);

private:
    Severity m_severity;
    std::ostream *m_outputs[2];
};



#endif  
