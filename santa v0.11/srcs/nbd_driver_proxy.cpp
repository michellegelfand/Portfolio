/*
    Sets up nbd driver proxy;
    ntohl & ntohll for transforming little endian to big endian 
    for network and vice versa.
    request: READ writes from storage to request buffer
             WRITE writes from request buffer to storage
    reply:  WRITE: returns reply OK
            READ: returns OK + buffer read  

*/

#include <fcntl.h>//ioctl
#include <sys/socket.h> //socketpair
#include <sys/ioctl.h>//ioctl
#include <linux/nbd.h>//NBD_SET_SIZE, NBD_CLEAR_SOCKET
#include <iostream>//std::ref
#include<signal.h>  // sigfillset
#include <arpa/inet.h>//ntohl
#include <unistd.h>//close
#include <string.h>//memcpy

#include "../include/test_tools.hpp"
#include "../include/driver_data.hpp"
#include "../include/nbd_driver_proxy.hpp"
#include "../include/nbd_driver_proxy.hpp"
#include "../include/logger.hpp"
#include "../include/handleton.hpp"
#include "../include/factory.hpp"

namespace ilrd
{

#ifndef BUSE_DEBUG
  #define BUSE_DEBUG (0)
#endif


#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a) {
  return a;
}
#else
u_int64_t ntohll(u_int64_t a) {
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return ((u_int64_t) lo) << 32U | hi;
}
#endif

Logger* logger = Handleton<Logger>::get_instance();


struct nbd_error : public std::runtime_error
{
	nbd_error(const std::string& s = "nbd_error")
		: std::runtime_error(s)
    {

    }
};

template <typename T, typename... Types>
void call_ioctl(T var1, Types... var2)
{
	if(-1 == ioctl(var2...))
	{
         logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, var1);
		throw(nbd_error(var1));
	}
}

void NBDDriverProxy::read_all(int fd, char* buf, size_t count)
{
	int bytes_read;

	while (count > 0) 
	{
		bytes_read = read(fd, buf, count);
		buf += bytes_read;
		count -= bytes_read;

        if(0 < count)
        {
            throw nbd_error("read all failed");
        }
  	}
}

void NBDDriverProxy::write_all(int fd, char* buf, size_t count)
{
  	int bytes_written;

  	while (count > 0) 
  	{
		bytes_written = write(fd, buf, count);
		buf += bytes_written;
		count -= bytes_written;
    
        if(0 < count)
        {
            throw nbd_error("write all failed");
        }
    }
}



NBDDriverProxy::NBDDriverProxy(const std::string& dev_file, size_t storage_size)
: m_dev_fd(open(dev_file.c_str(), O_RDWR)), m_disconnect(0)
{   
    try
    {  
        //nbd opened in MIL
        call_ioctl("NBD_SET_SIZE failed",m_dev_fd, NBD_SET_SIZE, storage_size);

#ifdef DO_DEBUG
    std::cout << "\nim in NBDDriverProxy ctor\n";
#endif

        if(-1 ==  m_dev_fd)
        {
            throw nbd_error("nbd dp open() failed");
        }

        int sp[2];
        if(-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, sp))
        {
            throw nbd_error("nbd dp socketpair() failed");
        }
        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "socket pair set");

        m_nbd_fd = sp[0];
        ProxyDriver::set_fd(sp[1]);
logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t file descriptors set");
logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t Branching new thread");
        m_nbd_thread = std::thread(&NBDDriverProxy::m_thread_func, this);

        call_ioctl("NBD_CLEAR_SOCK failed",m_dev_fd, NBD_CLEAR_SOCK); 
    }
    catch(...)
    {
        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t nbd dtor threw exception");
        throw nbd_error("nbd dp ctor threw");
    }
}

NBDDriverProxy::NBDDriverProxy(const std::string& dev_file, 
                size_t block_size,  
                size_t num_blocks)
    :NBDDriverProxy(dev_file, block_size * num_blocks)
{
    logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t nbd dp inited");
}
                
NBDDriverProxy::~NBDDriverProxy() 
{
    try
    {
        if(0 == m_disconnect)
        {
            try
            {
                disconnect();
            }
            catch(...)
            {
                throw nbd_error("disconnect threw");
            }
        }

        m_nbd_thread.join();

        //RAII
        close(ProxyDriver::get_fd());        
        close(m_nbd_fd);
        close(m_dev_fd); 
    }
    catch(const std::exception& e)
    {
         logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t nbd dtor threw exception");
    }
   
} 

void NBDDriverProxy::m_thread_func()
{
    //starts DOIT loop and listens for requests
#ifdef DO_DEBUG
    std::cout << "\nim in m_thread_func\n";
#endif
	sigset_t sigset;

    try
    {
        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t start DOIT loop, listening for requests");
        if((0 != sigfillset(&sigset)) ||
        (0 != pthread_sigmask(SIG_SETMASK, &sigset, 0))) 
        {
            throw nbd_error("\nnbd dp failed sigmask");
        }

        call_ioctl("\nnbd dp  failed to set socket",m_dev_fd, NBD_SET_SOCK, m_nbd_fd);
    
        set_flags();


#ifdef DO_DEBUG
        std::cout << "\nnow entering do-it";
#endif
        call_ioctl("\fnbd dp  failed do_it",m_dev_fd, NBD_DO_IT);

        call_ioctl("\nnbd dp  failed NBD_CLEAR_QUE",m_dev_fd, NBD_CLEAR_QUE);
        call_ioctl("\nnbd dp  failed NBD_CLEAR_SOCK",m_dev_fd, NBD_CLEAR_SOCK);
    }
    catch(nbd_error& e) 
    {
        std::cerr << "\nnbd error: " << e.what() << '\n';
    }

}

std::unique_ptr<DriverData> NBDDriverProxy::receive_request() 
{
    
	struct nbd_request request;
	int bytes_read = 0;

	bytes_read = read(ProxyDriver::get_fd(), &request, sizeof(request));
	
    if(bytes_read != sizeof(request))
	{

        throw(nbd_error("receive_request - bytes_read Failed"));
	}

    std::unique_ptr<DriverData> received_request(new DriverData(
                   static_cast<DriverData::action_type_t>(ntohl(request.type)),
                   request.handle, 
                   ntohll(request.from), 
                   ntohl(request.len)));

    if(received_request->get_type() == DriverData::action_type_t::WRITE)
    {
        read_all(ProxyDriver::get_fd(), received_request->access_buffer().data(),
                                        received_request->get_length());
    }


#ifdef DO_DEBUG
	std::cout << "\tReceiving request: fd:  " << ProxyDriver::get_fd() <<
 " offset: " << ntohll(request.from) << " len " << ntohl(request.len)<< std::endl;
#endif

    return received_request;
}

void NBDDriverProxy::send_reply(std::unique_ptr<DriverData> data)
{
    // reply:  WRITE: returns reply OK
    //        READ: returns OK + buffer read  

	struct nbd_reply reply;
	DriverData::action_type type = data->get_type();

	reply.error = htonl(0);
	reply.magic = htonl(NBD_REPLY_MAGIC);

    memcpy(reply.handle, data->get_handle(), data->get_handle_size());

	write_all(ProxyDriver::get_fd(), reinterpret_cast<char*>(&reply),sizeof(struct nbd_reply));

    if(DriverData::action_type_t::READ == type)
	{
		write_all(ProxyDriver::get_fd(), data->access_buffer().data(), data->get_length());
	}


#ifdef DO_DEBUG
	std::cout << "\t Sending Reply: fd " << get_fd() <<" offset: "<< data->get_offset() << " len: " << data->get_length();
#endif
 logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t Sending Reply");
}

void NBDDriverProxy::disconnect()
{
    if (0 == m_disconnect ) 
    {
#ifdef DO_DEBUG
        std::cout << "\ndisconnecting"<<std::endl;
#endif
        call_ioctl("\nfailed to disconnect",
                    m_dev_fd, NBD_DISCONNECT);              
    }

#ifdef DO_DEBUG
    std::cout << "ioctl called. exiting gracefully" << std::endl;
#endif
logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t gracefully disconnected");
    m_disconnect = 1; 

}


void NBDDriverProxy::set_flags()
{
//flags for inner usage of nbd
	int flags = 0;
#if defined NBD_SET_FLAGS
    flags = 0;

#if defined NBD_FLAG_SEND_TRIM
    flags |= NBD_FLAG_SEND_TRIM;
#endif

#if defined NBD_FLAG_SEND_FLUSH
    flags |= NBD_FLAG_SEND_FLUSH;
#endif

    if (flags != 0 && -1 ==  ioctl(m_dev_fd, NBD_SET_FLAGS, flags))
    {
        throw nbd_error("\nNBD Set flags failed");
    }


#endif

}
    
} // namespace ilrd


