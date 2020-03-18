#include "composit.h"

namespace ilrd
{

Composite::Composite()
{
}

Composite::~Composite()
{
}

void Composite::AddShape(Shape *new_shape)
{
    m_shape_vector.push_back(new_shape);
}  

void Composite::DrawImp()
{
    size_t size = m_shape_vector.size();

    for(size_t i=0; i<size; ++i)
    {
        m_shape_vector[i]->Draw();
    }
}

void Composite::SetPosition(const Point& position)
{
    size_t size = m_shape_vector.size();

    for(size_t i = 0; i< size; ++i)
    {
        m_shape_vector[i]->SetPosition(m_shape_vector[i]->GetPosition() - position);
    }

    Shape::SetPosition(position); 
}


void Composite::SetColor(color_t color)
{
    size_t size = m_shape_vector.size();

    for(size_t i = 0; i< size; ++i)
    {
        m_shape_vector[i]->SetColor(color);
    }

    Shape::SetColor(color); 
}

void Composite::SetAngle(double angle)
{
    size_t size = m_shape_vector.size();

    for(size_t i = 0; i< size; ++i)
    {
        m_shape_vector[i]->SetAngle(angle);
    }

    Shape::SetAngle(angle); 
}


void Composite::Revolve(const Point& axis, double angle)
{
    size_t size = m_shape_vector.size();

    for(size_t i = 0; i< size; ++i)
    {
        m_shape_vector[i]->Revolve(axis, angle);
    }
}












}//ilrd