#ifndef  __RECTENGLE_H__
#define  __RECTENGLE_H__

#include "shape.h"

namespace ilrd
{

class Rectangle: public Shape
{
public:
    explicit Rectangle(std::size_t hieght, std::size_t width);
    virtual ~Rectangle();

private:
    virtual void DrawImp();
    std::size_t m_height;
    std::size_t m_width;
};

}//namespace ilrd

#endif //__RECTENGLE_H__
