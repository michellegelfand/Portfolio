#pragma once
#include "Polygon.h"

class Arrow : public Shape
{
public:
	Arrow(const Point& a, const Point& b, const std::string& type, const std::string& name);
	~Arrow();

	virtual void draw(const Canvas& canvas) override;
	virtual void clearDraw(const Canvas& canvas) override;

	virtual double getArea() const override;
	virtual double getPerimeter() const override;

	virtual void move(const Point& other) override;

private:
	std::vector<Point> _points;
};