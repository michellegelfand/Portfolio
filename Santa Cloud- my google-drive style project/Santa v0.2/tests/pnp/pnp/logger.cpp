#include <iostream>         
#include <fstream>          //ofstream
#include <mutex>            //mutex
#include <iomanip>          //std::put_time
#include <ctime>            //time
#include <thread>           //std::thread, this_thread, get_id
#include <unistd.h>         //close

#include "../include/lock_guard.hpp"
#include "../include/logger.hpp"
#include "../include/inbar_tools.hpp"

namespace ilrd
{

Logger::Logger(Severity severity)
    : m_severity(severity)
{
    DEBUG_ONLY(std::cout << "Logger Ctor" <<std::endl);

    static std::ofstream dev_null("/dev/null");
    static std::ofstream output("log_file.txt");

    m_lut[0] = &dev_null;
    m_lut[1] = &output;
}

Logger::~Logger()
{
    DEBUG_ONLY(std::cout << "Logger Dtor" << std::endl);
    m_lut[0]->close();
    m_lut[1]->close();
}
void Logger::Log(Severity msg_severity, const std::string& msg,
                    const std::string &file, int line)
{
    LockGuard<std::mutex> lock(&m_mutex);
    std::time_t start_time = std::time(nullptr);
    std::tm tm = *std::localtime(&start_time);
    
    std::cout << "Severity: " << msg_severity << std::endl 
                         << "File: " << file << " Line: " << line << std::endl
                         << "Thread number: " << std::this_thread::get_id()
                         << std::endl << GRN "Message: " NRM << msg
                         << std::endl << std::endl;
    
    *m_lut[msg_severity >= m_severity] << 
        msg <<"\n" << 
        std::put_time(&tm, "(%Y/%m/%d %H:%M:%S) ") << 
        "File: " << file << 
        ", Line: " << line << 
        ", Thread number: " << std::this_thread::get_id() << std::endl;
}

void Logger::SetOutputSevirity(Severity output_severity)
{
    m_severity = output_severity;
}

}
