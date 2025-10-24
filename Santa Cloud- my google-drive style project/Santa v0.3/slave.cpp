/* 
 * Creating DriverProxy, Storage and Monitor Base. 
 * Passing requests to DriverProxy to Storage.
 * exit with Ctrl+c - graceful exit.
 * 
 * Receives command line arguments: device name and 
 *                                  logging severity level(as int): INFO = 0
 *                                                                  INFO = 1
 *                                                                  WARNING = 2
 *                                                                  ERROR = 3
 * Default logging severity is WARNING.
 * 
 * File:   santacloud.cpp
 * Date:   10.11.19
 * Author: Michelle Gelfand
 * */

#include <iostream>     // cout
#include <csignal>      // signal
#include <cstring>      // signal
#include <algorithm>    // transform
#include <exception>    // std::runtime_error
#include <cstddef>      // std::nullptr
#include <memory>       // std::unique_ptr
#include <unistd.h>		// STDIN_FILENO		
#include <string>       // std::string
#include <cstdlib>      // atoi
#include <mutex>        // std::mutex
#include <thread>       // std::thread
#include <atomic>       // std::atomic

#include "include/factory.hpp"              //task creation
#include "include/slave_driver.hpp"         //driver implementation
#include "include/mmap_storage.hpp"         //storage implementation
#include "include/driver_data.hpp"          //data passed between driver and storage
#include "include/epoll_wrapper.hpp"                //fd polling implementation using epoll
#include "include/logger.hpp"               //logger
#include "include/handleton.hpp"            //single instance even in shared objects
#include "include/thread_pool.hpp"          //task handling
#include "include/slave_tasks.hpp"                //task implementations
#include "include/waitable_pqueue.hpp"      //for storing and retrieving tasks
#include "include/request_engine.hpp"       //request engine
#include "include/slave_gateway.hpp"        //slave gateway


using namespace ilrd;

int* should_run = nullptr;

//sets logger output in accordance with severity
void set_logger_severity_output(int severity);

//Functions for handling signals to allow graceful disconnect
static void set_sigaction(int sig, const struct sigaction * act);
void sighandler(int sig);
void handle_signals();

//Request engine typedefs and functions
using TaskFactory = Factory<RETask, 
                            unsigned int,
                            std::unique_ptr<DriverData>,
                            std::unique_ptr<DriverProxy>&,
                            std::unique_ptr<Storage>&,
                            bool&>;

void init_request_engine(RequestEngine<unsigned int, ArgData>& re,
                        GateWay<unsigned int, ArgData>* slave_gw);

void write_all(std::unique_ptr<DriverProxy>& my_driver, 
            const std::string& start_message);


int main(int argc, char** argv)
{
    //#ifdef DO_DEBUG
	std::cout << "slave main" << std::endl;

//#endif
    const size_t STORAGE_SIZE = 67108864 * 2;

    try
    {
        if(2 > argc)
        {

            return -1;
        }
        
        /// if(3 == argc)
        //{
            /* set_logger_severity_output(std::atoi(argv[1])); */
        //} 
/* 
        Handleton<Logger>::get_instance()->Log(
                            Logger::Severity::INFO, 
                            std::this_thread::get_id(),
                            "~",
                            __FILE__);
                            __LINE__, 
                            std::string("Slave : ")
                            + "STORAGE_SIZE: " + std::to_string(STORAGE_SIZE),  */
        handle_signals();
  // #ifdef DO_DEBUG
	std::cout << "about to init request engine" << std::endl;

//#endif   
        RequestEngine<unsigned int, ArgData> re(
            "/home/student/Desktop/michelle-gelfand/projects/santa v0.31/monitor", 3);

//#ifdef DO_DEBUG
	std::cout << "request engine inited" << std::endl;

//#endif

        //Creating pointers to objects for the program and storing them in 
        //unique pointers to ensure Dtors are called when exiting scope.
        std::unique_ptr<Storage> my_storage(new MmapStorage(STORAGE_SIZE,
                                                            "mmap_storage.txt"));
//#ifdef DO_DEBUG
	std::cout << "storage inited" << std::endl;

//#endif
        std::unique_ptr<DriverProxy> my_driver(new SlaveDriver(atoi(argv[1])));

//#ifdef DO_DEBUG
	std::cout << "slave driver inited" << std::endl;

//#endif
        //Init global pointer to RequestEngine run flag to allow signal handler 
        //to shut down
        should_run = re.get_running_flag();
        
        SlaveGateWay slave_gw(my_driver->get_request_fd(), my_driver,                                 my_storage, (re.get_running_flag()));
//#ifdef DO_DEBUG
	std::cout << "slave gateway inited" << std::endl;

//#endif
        init_request_engine(re, &slave_gw);
//#ifdef DO_DEBUG
	std::cout << "request engine inited" << std::endl;

//#endif
       /*  Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::INFO, 
                        std::string("Main: Enter Request Engine Run"), 
                        __LINE__, 
                        __FILE__); */

        std::string start_message("Hi Master I am your slave");

        write_all(my_driver, start_message);
//#ifdef DO_DEBUG
	std::cout << "written all" << std::endl;

//#endif
        re.run();
    
       /*  Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::INFO, 
                        std::string("Out of while"), 
                        __LINE__, 
                        __FILE__); */
    }
    catch(const std::exception& e)
    {
       /*  Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::ERROR, 
                        std::string("Main has thrown") + e.what(), 
                        __LINE__, 
                        __FILE__);
        std::cerr << e.what() << std::endl; */
        //#ifdef DO_DEBUG
	std::cout << "slave main exception thrown" << std::endl;

//#endif
    }

    return 0;
}

void set_logger_severity_output(int severity)
{
    switch (severity)
    {
    /* case 0:
        Handleton<Logger>::get_instance()->SetOutputSeverity(Logger::Severity::INFO);
        break;
    case 1:
        Handleton<Logger>::get_instance()->SetOutputSeverity(Logger::Severity::INFO);
        break;
    case 2:
        Handleton<Logger>::get_instance()->SetOutputSeverity(Logger::Severity::WARNING);
        break;
    case 3:
        Handleton<Logger>::get_instance()->SetOutputSeverity(Logger::Severity::ERROR);
        break;
    default:
        break; */
    }
}

void init_request_engine(RequestEngine<unsigned int, ArgData>& re,
                        GateWay<unsigned int, ArgData>* slave_gw)
{
    re.add_task(static_cast<unsigned int>(DriverData::action_type_t::READ), 
                SlaveReadTask::create);
               // #ifdef DO_DEBUG
	std::cout << "re: slave task added 1/2" << std::endl;

//#endif
    re.add_task(static_cast<unsigned int>(DriverData::action_type_t::WRITE), 
                SlaveWriteTask::create);
//#ifdef DO_DEBUG
	std::cout << "re: slave task added 2/2" << std::endl;

//#endif
    re.add_gateway(slave_gw);
//#ifdef DO_DEBUG
    std::cout << "re: gateway added" << std::endl;
//#endif
}

void write_all(std::unique_ptr<DriverProxy>& my_driver, 
            const std::string& start_message)
{
   // #ifdef DO_DEBUG
	std::cout << "entered write all" << std::endl;

//#endif
    int bytes_written = 0;

    size_t count = start_message.length() + 1;
    char* buffer = const_cast<char*>(start_message.c_str());

    while(count) 
    {
        bytes_written = write(my_driver->get_request_fd(), 
                                buffer, 
                                count);

        if(0 < bytes_written)
        {
            buffer += bytes_written;
            count -= bytes_written;
        }
    }
}

//signal handling setup functions
static void set_sigaction(int sig, const struct sigaction *act) 
{
    if(sigaction(sig, act, nullptr)) 
    {
      /*   Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::ERROR, 
                        std::string("Signal handler setup failed"), 
                        __LINE__, 
                        __FILE__);
        throw(std::runtime_error("Signal handler setup failed")); */
    }
}

void sighandler(int sig)
{
    (void)sig;

    *should_run = 0;
}

void handle_signals()
{
    struct sigaction act;

    act.sa_handler = sighandler;
    act.sa_flags = SA_RESTART;

   /*  Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::INFO, 
                        std::string("Setting up signal handlers"), 
                        __LINE__, 
                        __FILE__); */

    if(sigemptyset(&act.sa_mask) || 
       sigaddset(&act.sa_mask, SIGINT) || 
       sigaddset(&act.sa_mask, SIGTERM)) 
    {
       /*  Handleton<Logger>::get_instance()->Log(
                        Logger::Severity::ERROR, 
                        std::string("failed to prepare signal mask"), 
                        __LINE__, 
                        __FILE__);
        throw(std::runtime_error("failed to prepare signal mask")); */
    }

    set_sigaction(SIGINT, &act); 
    set_sigaction(SIGTERM, &act);
}


