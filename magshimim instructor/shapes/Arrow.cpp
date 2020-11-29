#include "Arrow.h"

double Arrow::getArea() const
{
	return 0.0;
}

double Arrow::getPerimeter() const
{
	return _points[0].distance(_points[1]);
}

Arrow::Arrow(const Point& a, const Point& b, const std::string& type, const std::string& name)
	:Shape(name, type)
{
	_points.push_back(a);
	_points.push_back(b);
}

Arrow::~Arrow()
{ 
	_points.clear();
}

void Arrow::draw(const Canvas& canvas)
{
	canvas.draw_arrow(_points[0], _points[1]);
}
void Arrow::move(const Point& other)
{
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i] += other;
	}
}
void Arrow::clearDraw(const Canvas& canvas)
{
	canvas.clear_arrow(_points[0], _points[1]);
}


