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

using namespace ilrd;

void set_sigaction(int signal, struct sigaction* action);
void sighandler(int sig);
void set_sighandler();

const size_t STORAGE_SIZE = 128000000;

NBDDriverProxy* g_nbd_driver;
Logger* logger = Handleton<Logger>::get_instance();

int main()
{
	try
	{
		std::ofstream logfile("santa.log",std::ofstream::app);
		logger->SetOutput(logfile);

		logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "Program launched. Logger inited.");

		set_sighandler();

		RAMStorage storage(STORAGE_SIZE);
		NBDDriverProxy nbd_driver("/dev/nbd0", std::size_t(STORAGE_SIZE));
		
		int running = 1;

		g_nbd_driver = &nbd_driver;
	
		std::unique_ptr<DriverData> request;
		std::unique_ptr<DriverData> reply;

		epoll_wrapper epoll(10);
		epoll.add(nbd_driver.get_fd(), EPOLLIN);
		epoll.add(STDIN_FILENO, EPOLLIN);
		logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "epoll inited, now running.");
		while(running)
		{
			int num_events = epoll.wait(-1);

			for(int i = 0; i < num_events; ++i)
			{
				if (epoll[i] == nbd_driver.get_fd())
				{
					request = nbd_driver.receive_request();

					switch(request->get_type())
					{
						case DriverData::action_type_t::READ:
						reply = storage.read(std::move(request));
#ifdef DO_DEBUG
	std::cout << "\tREAD:\n " ;
#endif
						logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "recieved reading request");
						break;
					
						case DriverData::action_type_t::WRITE:
						reply = storage.write(std::move(request));
#ifdef DO_DEBUG
	std::cout << "\tWRITE:\n " ;
#endif
						logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "recieved writing request");
						break;

						case DriverData::action_type_t::DISCONNECT:
						reply = std::move(request);
						running = 0;
							
						break;
						
						default:
						reply = std::move(request);
						break;
					}
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
				
				nbd_driver.send_reply(std::move(reply));
			}

		}
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "caught" << std::endl;
	}

	return 0;
}


void sighandler(int sig)
{
	(void)sig;
	
	g_nbd_driver->disconnect();	

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
	
