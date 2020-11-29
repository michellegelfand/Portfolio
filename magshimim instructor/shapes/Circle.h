#pragma once

#include "Shape.h"
#include "Point.h"

#define PI 3.14

class Circle : public Shape
{
public:
	Circle(const Point& center, double radius, const std::string& type, const std::string& name);
	~Circle();

	const Point& getCenter() const;
	double getRadius() const;

	virtual void draw(const Canvas& canvas);
	virtual void clearDraw(const Canvas& canvas);

	virtual double getArea() const override;
	virtual double getPerimeter() const override;
	virtual void move(const Point& other) override;


private:

	double _radius;
	Point _middle;
};