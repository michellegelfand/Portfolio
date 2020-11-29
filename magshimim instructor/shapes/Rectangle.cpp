#include "Rectangle.h"



myShapes::Rectangle::Rectangle(const Point& a, double length, double width, const std::string& type, const std::string& name)
	:Polygon(type, name), _length(length), _width(width)
{
	if (length <= 0 || width <= 0)
	{
		throw std::exception("Rectangle: attempted to init with non-positive width or height\n");
	}

	_points.push_back(a);
	
	double p2x = a.getX() + width;
	double p2y = a.getY() + length;
	_points.push_back(std::move(Point(p2x, p2y)));
}

myShapes::Rectangle::~Rectangle()
{
}

double myShapes::Rectangle::getArea() const
{
	return _length * _width;
}

double myShapes::Rectangle::getPerimeter() const
{
	return 2 * _length + 2 * _width;
}

void myShapes::Rectangle::draw(const Canvas& canvas)
{
	canvas.draw_rectangle(_points[0], _points[1]);
}


void myShapes::Rectangle::clearDraw(const Canvas& canvas)
{
	canvas.clear_rectangle(_points[0], _points[1]);
}


