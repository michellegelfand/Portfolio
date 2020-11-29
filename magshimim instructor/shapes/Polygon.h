#pragma once

#include "Shape.h"
#include "Point.h"
#include <vector>

class Polygon : public Shape
{
public:
	Polygon(const std::string& type, const std::string& name);
	~Polygon();
	virtual double getArea() const override;
	virtual double getPerimeter() const override;
	virtual void draw(const Canvas& canvas) override;
	virtual void clearDraw(const Canvas& canvas) override;
	virtual void move(const Point& other) override;

protected:
	std::vector<Point> _points;
};