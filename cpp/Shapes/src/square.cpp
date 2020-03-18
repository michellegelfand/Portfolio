
#include "shape.h"
#include "square.h"

namespace ilrd
{

Square::Square(size_t length)
    :m_length(length)
{
}

Square::~Square()
{
}

void Square::DrawImp()
{
    InitDrawPolygon(m_length, m_length);
}




}//ilrd