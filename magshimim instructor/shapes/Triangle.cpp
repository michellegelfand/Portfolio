#include "Triangle.h"



Triangle::Triangle(const Point& a, const Point& b, const Point& c, const std::string& type, const std::string& name)
	:Polygon(type, name)
{
	//check 3 points dont fall on straight line (using vectors) 
	Point v1(a.getX() - b.getX(), a.getY() - b.getY()); ;
	Point v2(b.getX() - c.getX(), c.getY()-c.getY()); 


	if (v2.getX()/v1.getX() == v2.getY()/v1.getY())
	{//check 3 points dont fall on same line
		throw std::exception("Triangle: recieved 3 points on same line\n");
	}
	_points.push_back(a);
	_points.push_back(b);
	_points.push_back(c);
}

Triangle::~Triangle()
{
}

double Triangle::getArea() const
{
	//calculating sides
	double a = abs(_points[0].getY() - _points[1].getY() / _points[0].getX() - _points[1].getX());
	double b = abs(_points[1].getY() - _points[2].getY() / _points[1].getX() - _points[2].getX());
	double c = abs(_points[2].getY() - _points[0].getY() / _points[2].getX() - _points[0].getX());
	 
	double s = (a + b + c) / 2; 

	return sqrt(s * (s - a) * (s - b) * (s - c)); //Hermon's formula
}

double Triangle::getPerimeter() const
{
	double side1 = abs(_points[0].getY() - _points[1].getY() / _points[0].getX() - _points[1].getX());
	double side2 = abs(_points[1].getY() - _points[2].getY() / _points[1].getX() - _points[2].getX());
	double side3 = abs(_points[2].getY() - _points[0].getY() / _points[2].getX() - _points[0].getX());

	return side1 + side2 + side3;
}

void Triangle::draw(const Canvas& canvas) 
{
	canvas.draw_triangle(_points[0], _points[1], _points[2]);
}

void Triangle::clearDraw(const Canvas& canvas)
{
	canvas.clear_triangle(_points[0], _points[1], _points[2]);
}
