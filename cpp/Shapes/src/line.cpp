
#include "line.h"

namespace ilrd
{

Line::Line(size_t length)
    :m_length(length)
{
}

Line::~Line()
{
}

void Line::DrawImp()
{
   InitDrawPolygon(m_length, 0);  
}

}//ilrd