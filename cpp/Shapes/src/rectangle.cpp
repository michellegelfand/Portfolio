#include "rectangle.h"

namespace ilrd
{

Rectangle::Rectangle(std::size_t hieght, std::size_t width)
    :m_height(hieght), m_width(width)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::DrawImp()
{
    InitDrawPolygon(m_height, m_width);
}


}//ilrd