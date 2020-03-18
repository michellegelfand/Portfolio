#ifndef  __LINE_H__
#define  __LINE_H__

#include "shape.h"

namespace ilrd
{

class Line: public Shape
{
public:
    explicit Line(size_t length);

    virtual ~Line();

private:
    virtual void DrawImp();
    size_t m_length;
};

} //namespace ilrd

#endif /*__LINE_H__*/