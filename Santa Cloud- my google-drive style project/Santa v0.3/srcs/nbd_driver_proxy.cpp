/*
    Sets up nbd driver proxy;
    ntohl & ntohll for transforming little endian to big endian 
    for network and vice versa.
    request: READ writes from storage to request buffer
             WRITE writes from request buffer to storage
    reply:  WRITE: returns reply OK
            READ: returns OK + buffer read  

*/

#include "../include/nbd_driver_proxy.hpp"
#include "../include/driver_data.hpp"
#include "../include/handleton.hpp"
#include "../include/logger.hpp"
#include "../include/lock_guard.hpp"
#include "../include/nbd_data.hpp"

#include <fcntl.h>     // open, O_RDWR, 
#include <sys/ioctl.h> // ioctl
#include <linux/nbd.h> // NBD_SET_SIZE, NBD_CLEAR_SOCK
#include <signal.h>    // sigfillset
#include <string.h>    // memcopy
#include <iostream>    // std::cout
#include <thread>      // thread
#include <unistd.h>    // read, write
#include <arpa/inet.h> // ntohl, htonl


namespace ilrd
{
#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(size_t a) 
{
    return a;
}
#else
u_int64_t ntohll(u_int64_t a) 
{
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return ((u_int64_t) lo) << 32U | hi;
}
#endif
#define htonll ntohll

static void read_all(int fd, char* buf, size_t count);
static void write_all(int fd, char* buf, size_t count);

Logger* logger = Handleton<Logger>::get_instance();

class nbd_error : public std::runtime_error
{
public:
	nbd_error(const std::string& s = "nbd_error thrown"): std::runtime_error(s) { }
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


NBDDriverProxy::NBDDriverProxy(const std::string& dev_file, size_t storage_size)
{

    try
    {
 #ifdef DO_DEBUG
    std::cout << "\nim in NBDDriverProxy ctor\n";
#endif
        int sp[2];

        if(-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, sp))
        {
           
            throw(nbd_error("nbd dp socket pair creation failed"));
        }

        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "socket pair set");
        m_nbd_fd = sp[1];
        DriverProxy::set_request_fd(sp[0]);

        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t file descriptors set");
        m_disconnect = 0;

        m_dev_fd = open(dev_file.c_str(), O_RDWR);

        if(-1 ==  m_dev_fd)
        {
            
            throw(nbd_error("nbd dp failed to open dev fd"));
        }

        call_ioctl("NBDDriverProxyset size failed", m_dev_fd, NBD_SET_SIZE, storage_size);
        call_ioctl("NBDDriverProxy clear socket failed", m_dev_fd, NBD_CLEAR_SOCK);

        m_nbd_thread = std::thread(&NBDDriverProxy::m_thread_func, this);
    }
    catch(const nbd_error& e)
    {
        close(DriverProxy::get_request_fd());       
        close(m_nbd_fd);
        close(m_dev_fd);

        
        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t nbd dtor threw exception");
        throw nbd_error("nbd dp ctor threw");
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
        int flags;

       	/* Block all signals to not get interrupted in ioctl(NBD_DO_IT) */
        if((0 != sigfillset(&sigset)) || (0 != pthread_sigmask(SIG_SETMASK, &sigset, NULL))) 
        {
        
            throw(nbd_error("thread_func - Failed to block signals"));
        }

        call_ioctl("thread_func - Failed to set socket",m_dev_fd, NBD_SET_SOCK, m_nbd_fd);

        #if defined NBD_SET_FLAGS
            flags = 0;
            
            #if defined NBD_FLAG_SEND_TRIM
                flags |= NBD_FLAG_SEND_TRIM;
            #endif

            #if defined NBD_FLAG_SEND_FLUSH
                flags |= NBD_FLAG_SEND_FLUSH;
            #endif

            if(0 != flags) 
            { 
                call_ioctl("thread_func - NBD_SET_FLAGS Failed",
                            m_dev_fd, NBD_SET_FLAGS, flags);
            }
        #endif

        logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t start DOIT loop, listening for requests");
        call_ioctl("\nnbd dp  failed do_it",m_dev_fd, NBD_DO_IT);
        call_ioctl("\nnbd dp  failed NBD_CLEAR_QUE",m_dev_fd, NBD_CLEAR_QUE);
        call_ioctl("\nnbd dp  failed NBD_CLEAR_SOCK",m_dev_fd, NBD_CLEAR_SOCK);
    }
    catch(const nbd_error& e)
    { 
        std::cerr << "\nnbd error: " << e.what() << '\n';
    }
}


NBDDriverProxy::NBDDriverProxy(const std::string& dev_file, 
                               size_t block_size, size_t num_blocks)
 :NBDDriverProxy(dev_file, (block_size * num_blocks))
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
            catch(const nbd_error& e)
            {
                throw nbd_error("disconnect threw");
            }
        }

        m_nbd_thread.join();

        //RAII
        close(DriverProxy::get_request_fd());        
        close(m_nbd_fd);
        close(m_dev_fd); 
    }
    catch(const std::exception& e)
    {
          logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t nbd dtor threw exception");
    }

}


std::unique_ptr<DriverData> NBDDriverProxy::receive_request()
{
	struct nbd_request request;
	int bytes_read = 0;
    static int request_id = 0;

	bytes_read = read(DriverProxy::get_request_fd(), &request, sizeof(request));
	
    if(bytes_read != sizeof(request))
	{

        throw(nbd_error("receive_request - bytes_read Failed"));
	}

    std::unique_ptr<DriverData> received_request(new NbdData(
                   ntohll(request.from), 
                   ntohl(request.len),
                   static_cast<DriverData::action_type_t>(ntohl(request.type)),
                    request_id++,
                   request.handle)); 

    // if write-request, read the buffer also
    if(received_request->get_type() == DriverData::action_type_t::WRITE)
    {
        read_all(DriverProxy::get_request_fd(), received_request->access_buffer().data(),
                                        received_request->get_length());
    }
#ifdef DO_DEBUG
	std::cout << "\tReceiving request: fd:  " << DriverProxy::get_request_fd() <<
 " offset: " << ntohll(request.from) << " len " << ntohl(request.len)<< std::endl;
#endif

    return received_request;
}


void NBDDriverProxy::send_reply(std::unique_ptr<DriverData> data)
{
    // reply:  WRITE: returns reply OK
    //        READ: returns OK + buffer read  
	struct nbd_reply reply;
	DriverData::action_type_t type = data->get_type();

	reply.error = htonl(0);
	reply.magic = htonl(NBD_REPLY_MAGIC);

    std::unique_ptr<NbdData> nbd_data(static_cast<NbdData*>(data.get()));
    
    std::copy(nbd_data->get_handle(), nbd_data->get_handle() + HANDLE_SIZE, 
                                                            &reply.handle[0]);

/* 
    memcpy(reply.handle, data->get_handle(), data->get_handle_size()); */

    Lockguard<std::mutex> lock(&m_reply_mutex);

	write_all(DriverProxy::get_request_fd(), reinterpret_cast<char*>(&reply),sizeof(struct nbd_reply));

    if(DriverData::action_type_t::READ == type)
	{
		write_all(DriverProxy::get_request_fd(), data->access_buffer().data(), data->get_length());
	}
#ifdef DO_DEBUG
	std::cout << "\t Sending Reply: fd " << get_request_fd() <<" offset: "<< data->get_offset() << " len: " << data->get_length();
#endif
 logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t Sending Reply");


}


void NBDDriverProxy::disconnect()
{
    if(0 == m_disconnect) 
    {
        #ifdef DO_DEBUG
            std::cout << "\ndisconnecting"<<std::endl;
        #endif

        call_ioctl("failed to request disconect on nbd device", m_dev_fd, NBD_DISCONNECT);

        std::cout << "-------after disconnect-----" << std::endl;

    }

#ifdef DO_DEBUG
    std::cout << "ioctl called. exiting gracefully" << std::endl;
#endif
logger->Log(Logger::INFO, std::this_thread::get_id(),"~", __FILE__, __LINE__, "\t gracefully disconnected");

    m_disconnect = 1;
}


static void read_all(int fd, char* buf, size_t count)
{
    int bytes_read;

	while(count > 0) 
	{
		bytes_read = read(fd, buf, count);
		buf   += bytes_read;
		count -= bytes_read;

#ifdef DO_DEBUG
        if(0 < count)
        {
            std::cout << "read all failed" << std::endl;
        }
#endif
  	}
}


static void write_all(int fd, char* buf, size_t count)
{
    int bytes_written;

  	while(count > 0)
  	{
		bytes_written = write(fd, buf, count);
		buf   += bytes_written;
		count -= bytes_written;

#ifdef DO_DEBUG
        if(0 < count)
        {
            std::cout << "write all failed" << std::endl;
        }
#endif
  	}
}

} // namespace ilrd
