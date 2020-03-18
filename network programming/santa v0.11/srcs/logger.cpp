#include <ctime>//time
#include <iomanip>//put time

#include "logger.hpp"


namespace ilrd
{

Logger::Logger(Severity initialSeverity, std::ostream& initialOutput)
    :m_severity(initialSeverity)
{
    static std::ofstream devnull("/dev/null");
    m_outputs[0] = &devnull;
    m_outputs[1] = &initialOutput;
}

void Logger::Log(Severity msgSeverity,
                        std::thread::id thread_id, 
                        const std::string& error_type,
                        const std::string& file,
                        int line, 
                        const char *msg)
{
    Lockguard<std::mutex>new_lock(&m_mutex);

    std::time_t start_time = std::time(nullptr);
    std::tm tm = *std::localtime(&start_time);

    *m_outputs[(msgSeverity >= m_severity)] << "\n[Msg] "<< msg << "\n[Thread_id] "<<thread_id <<\
    "\n[Error Type] " << error_type << " " <<"\n[Line] " << line << "\n[FILE] "<<file   << "\n[Time] "<< std::put_time(&tm, "(%d/%m/%Y  %H:%M:%S) \n") <<std::endl;
    m_mutex.unlock();
}

void Logger::Log(Severity msgSeverity,
                         std::thread::id thread_id, 
                        const std::string& error_type,
                        const std::string& file,
                        int line, 
                        const std::string &msg)
{
    Log(msgSeverity, thread_id , error_type, file ,line, msg.c_str());
}

void Logger::SetOutputSeverity(Severity SetOutputSeverity)
{
    m_severity = SetOutputSeverity;
}

void Logger::SetOutput(std::ostream &output)
{
    m_outputs[1] = &output;
}

}
