#include "Circle.h"


Circle::Circle(const Point& center, double radius, const std::string& type, const std::string& name)
	:Shape(name, type), _middle(center), _radius(radius)
{
}
 
Circle::~Circle()
{
}

const Point& Circle::getCenter() const
{
	return _middle;
}

double Circle::getRadius() const
{
	return _radius;
}

void Circle::draw(const Canvas& canvas)
{
	canvas.draw_circle(_middle, _radius);
}

void Circle::clearDraw(const Canvas& canvas)
{
	canvas.clear_circle(_middle, _radius);
}


double Circle::getArea() const
{
	return PI * _radius * _radius;
}
double Circle::getPerimeter() const
{
	return 2 * PI * _radius;
}
void Circle::move(const Point& other)
{
	_middle = other;
}

