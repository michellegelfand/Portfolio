#include "shape.h"


namespace ilrd{

Shape::Shape(Point position, double angle,
                                     color_t color)
    :m_position(position), m_angle(angle), m_color(color)
{
}

Shape::~Shape()
{
}

void Shape:: SetColor(color_t color)
{
    m_color = color;
}

Shape::color_t Shape::GetColor() const
{
    return m_color;
}

void Shape::SetAngle(double angle)
{
    m_angle = angle;
}
    
double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetPosition(const Point& position)
{
    m_position = position;
}

Point Shape::GetPosition() const
{
    return m_position;
}

void Shape::Draw()
{
    DrawImp();
}

double Shape::GetRadians(double angle)
{
    return angle*M_PI/180;
}
void Shape::Revolve(const Point& axis, double angle)
{
    m_position.Revolve(axis, GetRadians(angle));
    SetAngle(GetAngle() + angle/40);
}


void Shape::InitDrawPolygon(size_t width, size_t height)
{
    double x = m_position.GetX();
    double y = m_position.GetY();
    
    Point top_left((x- width/2), (y + height/2));
    Point top_right((x+width/2), (y + height/2));
    Point bottom_left((x - width/2), (y- height/2));
    Point bottom_right((x + width/2), (y- height/2));

    top_left.Revolve(m_position, m_angle);
    top_right.Revolve(m_position, m_angle);
    bottom_left.Revolve(m_position, m_angle);
    bottom_right.Revolve(m_position, m_angle);

    DrawPolygon(GetColor(), 4, (int)top_left.GetX(), (int)top_left.GetY(),
    (int)bottom_left.GetX(), (int)bottom_left.GetY(), (int)bottom_right.GetX(), (int)bottom_right.GetY(),
    (int)top_right.GetX(), (int)top_right.GetY()); 
}


}//ilrd
