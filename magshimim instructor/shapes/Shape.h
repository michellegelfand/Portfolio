#pragma once
#include <string>
#include <iostream>
#include "Point.h"
#include "Canvas.h"


class Shape 
{
public:
	Shape(const std::string& name, const std::string& type);
	virtual ~Shape() = default;
	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual void draw(const Canvas& canvas) = 0;
	virtual void move(const Point& other) = 0; // add the Point to all the points of shape
	void printDetails() const;
	std::string getType() const;
	std::string getName() const;

	virtual void clearDraw(const Canvas& canvas) = 0;

private:
	std::string _name;
	std::string _type;
};