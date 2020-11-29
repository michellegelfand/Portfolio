#include "Polygon.h"

Polygon::Polygon(const std::string& type, const std::string& name)
	:Shape(name, type)
{
}

Polygon::~Polygon()
{
	_points.clear();
}

double Polygon::getArea() const
{
	return 0.0;
}

double Polygon::getPerimeter() const
{
	return 0.0;
}

void Polygon::draw(const Canvas& canvas)
{
	
}

void Polygon::clearDraw(const Canvas& canvas)
{
}

void Polygon::move(const Point& other)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i] += other;
	}
}
