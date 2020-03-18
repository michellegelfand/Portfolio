#ifndef __GATEWAY_HPP__
#define __GATEWAY_HPP__

/**
 * An abstract class that can connect an input fd to the request engine.
 * Can be used to extract a request from an input fd,to allow creation of RETask.
 * 
 * Tempated on Data, that will hold all arguments needed for RETask creation to
 * be passed to the RequestEngine factory.
*/



namespace ilrd
{

template <typename Key, typename Args>
class GateWay
{
public:
    GateWay(int fd);
    virtual ~GateWay() = 0;

/*     GateWay(const GateWay& other) = delete;
    GateWay& operator=(const GateWay& other) = delete;
    GateWay(const GateWay&& other) = default;
    GateWay& operator=(const GateWay&& other) = default; */
    
    int get_fd();

    virtual std::pair<Key, Args> read() = 0;

private:
    int gw_fd;
};


template <typename Key, typename Args>
GateWay<Key, Args>::GateWay(int fd)
    :   gw_fd(fd)
{
#ifdef DO_DEBUG
    std::cout << "gateway dtor " << std::endl;
#endif
}

template <typename Key, typename Args>
int GateWay<Key, Args>::get_fd()
{
#ifdef DO_DEBUG
    std::cout << "gateway dtor " << std::endl;
#endif
    return gw_fd;
}

}//namespace ilrd

#endif //__GATEWAY_HPP__
