#ifndef  __CIRCLE_H__
#define  __CIRCLE_H__

#include "shape.h"

namespace ilrd
{

class Circle: public Shape
{
public:
    explicit Circle(std::size_t radius);
    ~Circle();
                                                                
private:
    virtual void DrawImp();
    std::size_t m_radius;
};

} //namespace ilrd

#endif // __CIRCLE_H__