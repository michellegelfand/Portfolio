#include "circle.h"

namespace ilrd
{
Circle::Circle(size_t radius)
    :m_radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::DrawImp()
{
    DrawCircle(GetColor(), GetPosition().GetX(), GetPosition().GetY(), m_radius);
}


}