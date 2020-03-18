

#include "logger.hpp"

Logger::Logger(Severity initialSeverity, std::ostream& initialOutput)
    :m_severity(initialSeverity)
{
    static std::ofstream devnull("/dev/null");
    m_outputs[0] = &devnull;
    m_outputs[1] = &initialOutput;
}

void Logger::Log(Severity msgSeverity, const char *msg)
{
    *m_outputs[(msgSeverity >= m_severity)] << msg;
}

void Logger::Log(Severity msgSeverity, const std::string &msg)
{
    Log(msgSeverity, msg.c_str());
}

void Logger::SetOutputSeverity(Severity SetOutputSeverity)
{
    m_severity = SetOutputSeverity;
}

void Logger::SetOutput(std::ostream &output)
{
    m_outputs[1] = &output;
}

