#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "shape.h"

namespace ilrd
{

class Square: public Shape
{
public:
    explicit Square(std::size_t length);
    virtual ~Square();

private:
    virtual void DrawImp();
    std::size_t m_length;
    
};

} //namespace ilrd
#endif //__SQUARE_H__