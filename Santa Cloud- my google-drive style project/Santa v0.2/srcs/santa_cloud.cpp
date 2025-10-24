/******************************************
*	ver 0.1
*	epoll listens on file descriptors for requests and replies.
*	as well as for STDIN for Quit or signal for ctrl C; 
*   exiting gracefully with sighandler calling disconnect
*
***********************************************/

#include <iostream> //cout
#include <signal.h> // sigaction
#include <unistd.h> //STDIN_FILENO
#include <string.h> //strcmp
#include <csignal>//signal


#include "../include/ram_storage.hpp"
#include "../include/driver_data.hpp"
#include "../include/nbd_driver_proxy.hpp"
#include "../include/driver_proxy.hpp"
#include "../include/epoll_wrapper.hpp"
#include "../include/logger.hpp"
#include "../include/handleton.hpp"
#include "../include/factory.hpp"
#include "../include/disk_storage.hpp"
#include "../include/tptask.hpp"
#include "../include/request_engine_tasks.hpp"
#include "../include/thread_pool.hpp"

using namespace ilrd;

void set_sigaction(int signal, struct sigaction* action);
void sighandler(int sig);
void set_sighandler();

const size_t STORAGE_SIZE = 128000000;

NBDDriverProxy* g_nbd_driver;
Logger* logger = Handleton<Logger>::get_instance();
int running = 1;

using TaskFactory = Factory<TPTask, 
                            unsigned int,//translate action type to int
                            std::unique_ptr<DriverData>,
                            ProxyDriver&,
                            Storage&,
                            int>;

void setup_factory(TaskFactory& task_factory);

ThreadPool thread_pool;

int main()
{
	try
	{
		std::ofstream logfile("santa.log",std::ofstream::app);
		logger->SetOutput(logfile);

		logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "Program launched. Logger inited.");

		set_sighandler();

		DiskStorage storage("./disk_storage.txt",STORAGE_SIZE);
		NBDDriverProxy nbd_driver("/dev/nbd2", std::size_t(STORAGE_SIZE));

		g_nbd_driver = &nbd_driver;
	
		TaskFactory task_factory;

		setup_factory(task_factory);

		std::unique_ptr<DriverData> request;
		std::unique_ptr<DriverData> reply;

		epoll_wrapper epoll(10);
		epoll.add(nbd_driver.get_fd(), EPOLLIN);
		epoll.add(STDIN_FILENO, EPOLLIN);



		logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "epoll inited, now running.");
		
		while(running)
		{
			int num_events = epoll.wait(-1);
			std::cout << "num events set" << std::endl;
			if( -1 == num_events) 
			{
				std::cout << "num events -1" << std::endl;
				break;
			}
				
			for(int i = 0; i < num_events; ++i)
			{
				if (epoll[i] == nbd_driver.get_fd())
				{
					request = nbd_driver.receive_request();
					unsigned int type = request->get_type();

					 std::unique_ptr<TPTask> new_task =
                                    task_factory.create(type, 
                                                        std::move(request),
                                                        nbd_driver,
                                                        storage,
                                                        running);
					
                    thread_pool.add_task(std::move(new_task));
					/* std::thread th(request_handler, std::move(request),
							   std::ref(storage), std::ref(nbd_driver));
					th.detach();
 */
				/* 	request_handler(std::move(request),std::ref(storage) ,std::ref(nbd_driver)); */
				}
				else if(epoll[i] == STDIN_FILENO)
				{
					ssize_t r_bytes_from_stdin = 12;
				 	ssize_t r_bytes = 0;
				 	char buffer[1024]; 

				 	r_bytes = read(STDIN_FILENO, buffer, r_bytes_from_stdin);
					buffer[r_bytes] = '\0';

				 	if (0 == strcmp(buffer, "Quit\n"))
				 	{
				 		epoll.remove(nbd_driver.get_fd());
				 		epoll.remove(STDIN_FILENO);
						running = 0;
				 		nbd_driver.disconnect();
				 		break;
					}
				}
			}

		}
		thread_pool.stop(std::chrono::seconds(0));
		std::cout << "im out of while" << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << "Exception test: " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Exception test: " << std::endl;
	}

	return 0;
}


void sighandler(int sig)
{
	(void)sig;

	g_nbd_driver->disconnect();	
	running = 0;

}

void set_sigaction(int signal, struct sigaction* action)
{
	if(-1 == sigaction(signal, action, NULL))
	{
		throw std::runtime_error("sigaction");
	}
	logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "sigaction set");
}

void set_sighandler()
{
	if( (std::signal(SIGTERM,sighandler)!= 0) ||
		(std::signal(SIGINT,sighandler)!= 0) )
	{
		throw std::runtime_error("Set signal handlers failed");
	}
}



void setup_factory(TaskFactory& task_factory)
{
    task_factory.add(DriverData::action_type::READ, ReadTask::create);
    task_factory.add(DriverData::action_type::WRITE, WriteTask::create);
    task_factory.add(DriverData::action_type::DISCONNECT, DisconnectTask::create);
    task_factory.add(DriverData::action_type::TRIM, ReplyTask::create);
    task_factory.add(DriverData::action_type::FLUSH, ReplyTask::create);
}

	
